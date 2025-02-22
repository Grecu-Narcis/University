import {
  deleteRecordFromServer,
  getCategoriesFromServer,
  getRecordDetailsFromServer,
  getRecordsForCategoryFromServer,
  getRecordsFromServer,
  IP,
  postRecordToServer,
  updateRecordOnServer,
} from "@/repository/NetworkRepository";
import { SplashScreen } from "expo-router";
import { createContext, useEffect, useState } from "react";
import { showMessage } from "react-native-flash-message";
import * as SQLite from "expo-sqlite";
import {
  addCategoryRecordDb,
  addFetchedRecordDb,
  addRecordDb,
  addToSyncQueue,
  clearLocalDb,
  clearSyncQueue,
  createTable,
  deleteRecordDb,
  getAllCategoriesDb,
  getAllFetchedRecordsDb,
  getAllRecordsDb,
  getSyncQueue,
  removeFromSyncQueue,
  updateRecordDb,
} from "@/repository/SQLRepository";

type RecordContextType = {
  records: Item[];
  categories: string[];
  addRecord: (record: Item) => Promise<void>;
  updateRecord: (record: Item) => Promise<void>;
  deleteRecord: (recordId: number) => Promise<void>;
  getRecords: () => Promise<void>;
  getRecordDetails?: (recordId: number) => Promise<Item | null>;
  isLoaded?: boolean;
  isLoading: boolean;
  retryFetch?: () => Promise<void>;
  getRecordsList?: (category: string) => Promise<Item[]>;
};

export const RecordContext = createContext<RecordContextType | null>(null);

export default function RecordContextProvider({ children }: any) {
  const [records, setRecords] = useState<Item[]>([]);
  const [categories, setCategories] = useState<string[]>([]);
  const [isLoaded, setIsLoaded] = useState<boolean>(false);
  const [isLoading, setIsLoading] = useState<boolean>(true);

  const [fetchedFor, setFetchedFor] = useState<number[]>([]);

  const [dbConnection, setDbConnection] = useState<SQLite.SQLiteDatabase>();

  const addRecord = async (record: Item) => {
    try {
      const receivedRecord = await postRecordToServer(record);

      setRecords((prevRecords) => [...prevRecords, receivedRecord]);
    } catch (error) {
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  const updateRecord = async (record: Item) => {
    try {
      // await updateRecordOnServer(record.id);
      // Update the record in the database
      await updateRecordDb(dbConnection!, record);
      console.log("received: ");
      console.log(record);

      // Update the record in the local state
      setRecords((prevRecords) =>
        prevRecords.map((item) => (item.id == record.id ? record : item))
      );
    } catch (error) {
      console.error("Error updating record:", (error as Error).message);
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  const deleteRecord = async (recordId: number) => {
    try {
      await deleteRecordFromServer(recordId);
      // await deleteRecordDb(dbConnection!, recordId);

      setRecords((prevRecords) =>
        prevRecords.filter((record) => record.id != recordId)
      );
    } catch (error) {
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  const getRecords = async () => {
    try {
      if (records.length > 0) return;

      const result = await getRecordsFromServer();

      setRecords((prevRecords) => [...prevRecords, ...result]);
      setIsLoaded(true);
      // for (let record of result)
      //   await addRecordDb(dbConnection!, record).catch((error) =>
      //     console.log(error)
      //   );
    } catch (error) {
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    } finally {
      setIsLoading(false);
    }
  };

  const getRecordDetails = async (recordId: number) => {
    try {
      if (fetchedFor.find((entry) => entry == recordId))
        return records.find((record) => record.id == recordId)!;

      const result = await getRecordDetailsFromServer(recordId);
      setFetchedFor([...fetchedFor, recordId]);

      return result;
    } catch (error) {
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }

    return null;
  };

  const setupWebSocket = () => {
    const socket = new WebSocket(`ws://${IP}`);

    socket.onopen = () => {
      console.log("WebSocket connection established");
    };

    socket.onmessage = async (event) => {
      const receivedRecord: Item = JSON.parse(event.data);

      const formattedMessage = `New Recipe from category ${receivedRecord.category} named ${receivedRecord.title}$, rated as ${receivedRecord.rating} starts has been added`;

      showMessage({
        message: formattedMessage,
        duration: 5000,
        type: "info",
      });
    };

    socket.onclose = () => console.log("WebSocket connection closed");
  };

  useEffect(() => {
    SplashScreen.preventAutoHideAsync();

    const connection = SQLite.openDatabaseSync("shares.db");

    // createTable(connection);
    // clearLocalDb(connection);

    async function loadData() {
      // const result = await loadRecordsFromDb(connection);

      // if (result) return;

      await getRecords();
    }

    loadData();

    setDbConnection(connection);
    createTable(connection);

    setupWebSocket();
  }, []);

  return (
    <RecordContext.Provider
      value={{
        records: records,
        categories: categories,
        addRecord: addRecord,
        updateRecord: updateRecord,
        deleteRecord: deleteRecord,
        getRecords: getRecords,
        isLoaded: isLoaded,
        isLoading: isLoading,
        retryFetch: getRecords,
        getRecordDetails: getRecordDetails,
      }}
    >
      {children}
    </RecordContext.Provider>
  );
}

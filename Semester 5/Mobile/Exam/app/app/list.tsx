import { RecordContext } from "@/contexts/RecordsContext";
import { getAllItemsFromServer } from "@/repository/NetworkRepository";
import { useContext, useEffect, useState } from "react";
import { ActivityIndicator, FlatList, View, Text } from "react-native";
import { showMessage } from "react-native-flash-message";

type MonthlySpending = {
  category: string;
  totalSpending: number;
};

const InsightsScreen = () => {
  const [monthlySpending, setMonthlySpending] = useState<MonthlySpending[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);
  const recordsContext = useContext(RecordContext)!;

  const calculateMonthlySpending = (items: Item[]) => {
    const spendingMap = new Map<string, number>();

    // for (let item of items) {
    //   spendingMap.set(
    //     item.category,
    //     (spendingMap.get(item.category) || 0) + item.title
    //   );
    // }

    const sortedSpending = Array.from(spendingMap.entries())
      .map(([category, totalSpending]) => ({ category, totalSpending }))
      .sort((a, b) => b.totalSpending - a.totalSpending);

    setMonthlySpending(sortedSpending.slice(0, 3));
  };

  const fetchTransactions = async () => {
    setIsLoading(true);
    try {
      const result = await getAllItemsFromServer();
      calculateMonthlySpending(result);
    } catch (error) {
      console.log("2222");
      console.log((error as Error).message);
      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    } finally {
      setIsLoading(false);
    }
  };

  useEffect(() => {
    fetchTransactions();
  }, []);

  return (
    <View style={{ flex: 1, padding: 16 }}>
      {isLoading ? (
        <ActivityIndicator size="large" color="#0000ff" />
      ) : (
        <FlatList
          data={monthlySpending}
          keyExtractor={(item) => item.category}
          renderItem={({ item }) => (
            <View
              style={{
                flexDirection: "row",
                justifyContent: "space-between",
                padding: 8,
                borderBottomWidth: 1,
                borderColor: "#ccc",
              }}
            >
              <Text>
                {item.category}: {item.totalSpending}
              </Text>
            </View>
          )}
        />
      )}
    </View>
  );
};

export default InsightsScreen;

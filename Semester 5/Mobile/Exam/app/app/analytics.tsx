import CustomButton from "@/components/CustomButton";
import { RecordContext } from "@/contexts/RecordsContext";
import { getAllItemsFromServer } from "@/repository/NetworkRepository";
import React, { useContext, useEffect, useState } from "react";
import {
  View,
  Text,
  FlatList,
  StyleSheet,
  ActivityIndicator,
  SafeAreaView,
} from "react-native";
import { showMessage } from "react-native-flash-message";

type MonthlySpending = {
  month: string;
  averageRating: number;
};

const AnalyticsScreen = () => {
  const [monthlySpending, setMonthlySpending] = useState<MonthlySpending[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);
  const recordsContext = useContext(RecordContext)!;

  const calculateMonthlySpending = (items: Item[]) => {
    const spendingMap = new Map<string, { sum: number; count: number }>();

    for (let item of items) {
      const month = item.date.slice(0, 7); // Extract YYYY-MM from the date
      const current = spendingMap.get(month) || { sum: 0, count: 0 };

      spendingMap.set(month, {
        sum: current.sum + item.rating,
        count: current.count + 1,
      });
    }

    const sortedSpending = Array.from(spendingMap.entries())
      .map(([month, { sum, count }]) => ({
        month,
        averageRating: sum / count, // Calculate the average
      }))
      .sort((a, b) => b.averageRating - a.averageRating); // Sort by average rating descending

    setMonthlySpending(sortedSpending);
  };

  const fetchTransactions = async () => {
    setIsLoading(true);
    try {
      const result = await getAllItemsFromServer();
      calculateMonthlySpending(result);
    } catch (error) {
      showMessage({
        message: "Failed to load transactions!",
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
    <SafeAreaView style={{ flex: 1, padding: 16 }}>
      {isLoading ? (
        <ActivityIndicator size="large" color="#0000ff" />
      ) : (
        <FlatList
          data={monthlySpending}
          keyExtractor={(item) => item.month}
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
              <Text style={{ fontSize: 16 }}>{item.month}</Text>
              <Text style={{ fontSize: 16, fontWeight: "bold" }}>
                {item.averageRating.toFixed(2)}
              </Text>
            </View>
          )}
        />
      )}
    </SafeAreaView>
  );
};

export default AnalyticsScreen;

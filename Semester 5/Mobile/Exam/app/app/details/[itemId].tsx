import React, { useContext, useEffect, useState } from "react";
import {
  SafeAreaView,
  Text,
  StyleSheet,
  ActivityIndicator,
  FlatList,
  View,
  Button,
} from "react-native";
import { RecordContext } from "@/contexts/RecordsContext";
import { useLocalSearchParams, useRouter } from "expo-router";

export default function Details() {
  const recordsContext = useContext(RecordContext)!;
  const { itemId } = useLocalSearchParams(); // Assume `itemId` is passed as a route parameter
  const [item, setItem] = useState<Item | null>(null);
  const [loading, setLoading] = useState(true);

  const router = useRouter();

  const fetchDetails = async () => {
    if (itemId) {
      const result = await recordsContext.getRecordDetails!(
        parseInt(itemId as string)
      );

      setItem(result);
    }

    setLoading(false);
  };

  const handleDelete = async (itemId: number) => {
    setLoading(true);
    try {
      await recordsContext.deleteRecord(itemId);
      router.replace("/");
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchDetails();
  }, []);

  if (loading) {
    return (
      <SafeAreaView style={styles.main}>
        <ActivityIndicator size="large" color="#000" />
      </SafeAreaView>
    );
  }

  if (!item)
    return (
      <SafeAreaView>
        <Text>Failed to load item</Text>
      </SafeAreaView>
    );

  return (
    <SafeAreaView style={styles.main}>
      <View style={styles.itemContainer}>
        <Text style={styles.label}>
          ID: <Text style={styles.value}>{item.id}</Text>
        </Text>
        <Text style={styles.label}>
          Date: <Text style={styles.value}>{item.date}</Text>
        </Text>
        <Text style={styles.label}>
          Ttile: <Text style={styles.value}>{item.title}</Text>
        </Text>
        <Text style={styles.label}>
          Ingredients: <Text style={styles.value}>{item.ingredients}</Text>
        </Text>
        <Text style={styles.label}>
          Category: <Text style={styles.value}>{item.category}</Text>
        </Text>
        <Text style={styles.label}>
          Rating: <Text style={styles.value}>{item.rating}</Text>
        </Text>
      </View>
      <Button
        title="Delete Record"
        color="red"
        onPress={() => handleDelete(item.id)}
      />
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  main: {
    flex: 1,
    padding: 16,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#f8f8f8",
  },
  itemContainer: {
    marginBottom: 20,
    padding: 16,
    backgroundColor: "#fff",
    borderRadius: 8,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 2,
    width: "100%",
  },
  label: {
    fontSize: 16,
    fontWeight: "bold",
    marginBottom: 8,
  },
  value: {
    fontWeight: "normal",
  },
  errorText: {
    fontSize: 18,
    color: "red",
    textAlign: "center",
  },
});

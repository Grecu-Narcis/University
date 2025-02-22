import React, { useState, useContext } from "react";
import {
  View,
  Text,
  TextInput,
  Button,
  Alert,
  ActivityIndicator,
  StyleSheet,
} from "react-native";
import { useRouter } from "expo-router";
import { RecordContext } from "@/contexts/RecordsContext";

const AddItemScreen = () => {
  const [date, setDate] = useState("");
  const [title, setTitle] = useState("");
  const [ingredients, setIngredients] = useState("");
  const [category, setCategory] = useState("");
  const [rating, setRating] = useState("");

  const [showLoading, setShowLoading] = useState<boolean>(false);

  const recordsContext = useContext(RecordContext)!;
  const router = useRouter();

  const handleSubmit = async () => {
    if (!date || !title || !ingredients || !category || !rating) {
      Alert.alert("Please fill in all fields");
      return;
    }

    const newItem: Item = {
      id: -1, // Temporary ID, will be replaced by the backend or context
      date,
      title,
      ingredients,
      category,
      rating: parseFloat(rating), // Convert string to number
    };

    if (isNaN(newItem.rating)) {
      Alert.alert("Rating must be a valid number");
      return;
    }

    setShowLoading(true);
    try {
      await recordsContext.addRecord(newItem); // Ensure your context handles `Item` type
      Alert.alert("Item added successfully!");
      router.replace("/");
    } catch (error) {
      Alert.alert("Failed to add the item!");
    } finally {
      setShowLoading(false);
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Add New Item</Text>

      <TextInput
        style={styles.input}
        placeholder="Date (YYYY-MM-DD)"
        value={date}
        onChangeText={setDate}
        placeholderTextColor={"grey"}
      />
      <TextInput
        style={styles.input}
        placeholder="Title"
        value={title}
        onChangeText={setTitle}
        placeholderTextColor={"grey"}
      />
      <TextInput
        style={styles.input}
        placeholder="Ingredients"
        value={ingredients}
        onChangeText={setIngredients}
        placeholderTextColor={"grey"}
      />
      <TextInput
        style={styles.input}
        placeholder="Category"
        value={category}
        onChangeText={setCategory}
        placeholderTextColor={"grey"}
      />
      <TextInput
        style={styles.input}
        placeholder="Rating (numeric)"
        value={rating}
        keyboardType="numeric"
        onChangeText={setRating}
        placeholderTextColor={"grey"}
      />

      <Button title="Add Item" onPress={handleSubmit} />

      {showLoading && <ActivityIndicator size="large" />}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    justifyContent: "center",
    backgroundColor: "#f9f9f9",
  },
  header: {
    fontSize: 24,
    fontWeight: "bold",
    marginBottom: 20,
    textAlign: "center",
  },
  input: {
    height: 40,
    borderColor: "#ccc",
    borderWidth: 1,
    marginBottom: 15,
    paddingHorizontal: 10,
    borderRadius: 5,
  },
});

export default AddItemScreen;

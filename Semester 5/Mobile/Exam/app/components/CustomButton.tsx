import { Pressable, StyleSheet } from "react-native";
import { Text } from "react-native";

export default function CustomButton({ text, onPress }: any) {
  return (
    <Pressable onPress={onPress} style={styles.button}>
      <Text>{text}</Text>
    </Pressable>
  );
}

const styles = StyleSheet.create({
  button: {
    padding: 8,
    backgroundColor: "#5dade2",
    borderRadius: 16,
    alignItems: "center",
    marginTop: 8,
  },
});

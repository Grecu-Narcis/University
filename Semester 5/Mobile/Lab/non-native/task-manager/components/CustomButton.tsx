import { Pressable, StyleSheet, Text } from "react-native";

export type CustomButtonProps = {
  onClick: () => void;
  text: string;
};

export default function CustomButton({ onClick, text }: CustomButtonProps) {
  return (
    <Pressable onPress={onClick} style={styles.defaultButton}>
      <Text style={styles.defaultText}> {text} </Text>
    </Pressable>
  );
}

const styles = StyleSheet.create({
  defaultButton: {
    borderRadius: 12,
    backgroundColor: "#1A73D1",
    paddingHorizontal: 24,
    paddingVertical: 10,
  },

  defaultText: {
    color: "#F7FAFA",
    fontSize: 16,
    fontWeight: "bold",
    textAlign: "center",
  },
});

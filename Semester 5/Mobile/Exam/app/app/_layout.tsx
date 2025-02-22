import NetworkContextProvider from "@/contexts/NetworkContext";
import RecordContextProvider from "@/contexts/RecordsContext";
import { Stack } from "expo-router";
import FlashMessage from "react-native-flash-message";

export default function RootLayout() {
  return (
    <>
      <NetworkContextProvider>
        <RecordContextProvider>
          <Stack>
            <Stack.Screen name="index" options={{ headerShown: false }} />
            <Stack.Screen
              name="details/[itemId]"
              options={{ headerShown: false }}
            />
            <Stack.Screen name="add-item" options={{ headerShown: false }} />
            <Stack.Screen name="list" options={{ headerShown: false }} />
            <Stack.Screen name="analytics" options={{ headerShown: false }} />
          </Stack>
        </RecordContextProvider>
      </NetworkContextProvider>
      <FlashMessage position="top" />
    </>
  );
}

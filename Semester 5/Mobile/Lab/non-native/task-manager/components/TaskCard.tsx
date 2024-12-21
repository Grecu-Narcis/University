import { Task } from "@/domain/Task";
import { Alert, Image, Pressable, StyleSheet, Text, View } from "react-native";
import { CheckBox } from "@rneui/base";
import { useContext, useState } from "react";
import { TaskContext } from "@/context/TasksContext";
import { useRouter } from "expo-router";
import { showMessage } from "react-native-flash-message";

type TaskCardProps = {
  task: Task;
};

const maxTextLength = 25;

function getTitle(task: Task): string {
  return task.title.length > maxTextLength
    ? task.title.slice(0, maxTextLength) + "..."
    : task.title;
}

export default function TaskCard({ task }: TaskCardProps) {
  const taskContext = useContext(TaskContext)!;
  const router = useRouter();

  const updateStatus = () =>
    taskContext.updateTask({ ...task, isCompleted: !task.isCompleted });

  const deleteTask = () => {
    try {
      taskContext.deleteTask(task.taskId);
    } catch (error) {
      console.error((error as Error).message);

      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  const createConfirmDialog = () => {
    Alert.alert(
      "Delete confirmation",
      "Are you sure you want to remove this task?",
      [
        {
          text: "No",
          style: "cancel",
        },

        {
          text: "Yes",
          onPress: deleteTask,
        },
      ]
    );
  };

  return (
    <View style={styles.taskCard}>
      <CheckBox
        checked={task.isCompleted}
        onPress={updateStatus}
        containerStyle={{
          backgroundColor: "transparent",
          margin: 0,
          padding: 0,
        }}
        wrapperStyle={{ margin: 0, padding: 0 }}
        center={true}
      />

      <Text style={{ fontSize: 16, flex: 1 }}>{getTitle(task)}</Text>

      <View style={styles.row}>
        <Pressable
          onPress={() => {
            router.navigate(`./edit/${task.taskId}`);
          }}
          style={styles.editButton}
        >
          <Text style={styles.buttonText}>Edit</Text>
        </Pressable>

        <Pressable onPress={createConfirmDialog}>
          <Image source={require("../assets/images/trash.png")} />
        </Pressable>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  row: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    gap: 16,
  },

  taskCard: {
    width: "100%",
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    marginBottom: 16,
  },

  editButton: {
    borderRadius: 12,
    backgroundColor: "#1A73D1",
    paddingHorizontal: 24,
    paddingVertical: 10,
  },

  buttonText: {
    color: "#F7FAFA",
    fontSize: 16,
    fontWeight: "bold",
  },
});

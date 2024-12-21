import CustomButton from "@/components/CustomButton";
import { primary_text_color, secondary_text_color } from "@/constants/colors";
import { TaskContext } from "@/context/TasksContext";
import { useNavigation } from "expo-router";
import { useContext, useState } from "react";
import DateTimePicker from "@react-native-community/datetimepicker";
import { Picker } from "@react-native-picker/picker";
import { showMessage } from "react-native-flash-message";

import {
  Pressable,
  StyleSheet,
  Text,
  TextInput,
  View,
  Image,
  Alert,
} from "react-native";
import { SafeAreaProvider, SafeAreaView } from "react-native-safe-area-context";
import { TaskPriority } from "@/domain/TaskPriority";
import { Task } from "@/domain/Task";

interface AddOrEditProps {
  task: Task | undefined;
}

const validate = (task: Task) => {
  const errors: string[] = [];
  if (task.title.length < 3) {
    errors.push("Title must be at least 3 characters long");
  }

  if (task.description.length < 10)
    errors.push("Description must be at least 10 characters long");

  if (errors.length > 0)
    Alert.alert("Invalid values!", errors.join("\n"), [
      {
        text: "Ok",
      },
    ]);

  return errors.length > 0;
};

export default function AddOrEdit({ task }: AddOrEditProps) {
  const navigation = useNavigation();
  const tasksContext = useContext(TaskContext)!;

  const [title, setTitle] = useState<string>(task ? task.title : "");
  const [description, setDescription] = useState<string>(
    task ? task.description : ""
  );
  const [showDatePicker, setShowDatePicker] = useState<boolean>(false);
  const [date, setDate] = useState<Date>(task ? task.dueDate : new Date());
  const [priority, setPriority] = useState<TaskPriority>(
    task ? task.priority : TaskPriority.LOW
  );

  const onSave = () => {
    const taskToAdd: Task = {
      taskId: task ? task.taskId : 0,
      title: title,
      description: description,
      dueDate: date,
      isCompleted: false,
      priority: priority,
    };

    if (validate(taskToAdd)) return;

    try {
      task
        ? tasksContext.updateTask(taskToAdd)
        : tasksContext.addTask(taskToAdd);

      navigation.goBack();
    } catch (error) {
      console.error("Error on add/update:", (error as Error).message);

      showMessage({
        message: (error as Error).message,
        type: "warning",
        duration: 2000,
      });
    }
  };

  return (
    <SafeAreaProvider>
      <SafeAreaView
        style={{
          flex: 1,
          justifyContent: "center",
          alignItems: "center",
          margin: 16,
        }}
      >
        <Text style={styles.title}>{task ? "Edit task" : "New Task"}</Text>

        <View style={styles.mainContent}>
          <View style={styles.fields}>
            <View>
              <Text style={{ marginBottom: 8, fontWeight: "bold" }}>Title</Text>
              <TextInput
                style={styles.titleInput}
                placeholder="Title"
                onChangeText={setTitle}
                value={title}
              />
            </View>

            <View>
              <Text style={{ marginBottom: 8, fontWeight: "bold" }}>
                Description
              </Text>

              <TextInput
                multiline
                style={styles.descriptionInput}
                placeholder="Description"
                onChangeText={setDescription}
                value={description}
                textAlignVertical="top"
              />
            </View>

            <View nativeID="date-box" style={styles.dateBox}>
              <View nativeID="due-date">
                <Text
                  style={{ fontWeight: "medium", color: primary_text_color }}
                >
                  Due Date
                </Text>

                <Text style={{ color: secondary_text_color }}>
                  {date.toLocaleDateString()}
                </Text>
              </View>

              <Pressable
                nativeID="select-date"
                onPress={() => setShowDatePicker(true)}
              >
                <Image
                  source={require("../assets/images/date-picker.png")}
                  tintColor={primary_text_color}
                />
              </Pressable>
            </View>

            <View nativeID="priority" style={styles.priority}>
              <Text style={{ fontWeight: "bold" }}>Priority</Text>

              <Picker
                onValueChange={setPriority}
                style={{
                  minWidth: 150,
                  marginRight: -16,
                }}
                selectedValue={priority}
              >
                <Picker.Item label="Low" value={TaskPriority.LOW} />
                <Picker.Item label="Medium" value={TaskPriority.MEDIUM} />
                <Picker.Item label="High" value={TaskPriority.HIGH} />
              </Picker>
            </View>
          </View>

          <CustomButton
            onClick={() => {
              onSave();
            }}
            text="Save"
          />
        </View>

        {showDatePicker && (
          <DateTimePicker
            testID="dateTimePicker"
            value={date}
            mode={"date"}
            is24Hour={true}
            onChange={(event, selectedDate) => {
              if (selectedDate === undefined) return;

              setShowDatePicker(false);
              setDate(selectedDate);
            }}
          />
        )}
      </SafeAreaView>
    </SafeAreaProvider>
  );
}

const styles = StyleSheet.create({
  title: {
    fontWeight: "bold",
    fontSize: 18,
  },

  mainContent: {
    flex: 1,
    justifyContent: "space-between",
    width: "100%",
  },

  fields: {},

  titleInput: {
    height: 56,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    width: "100%",
    marginBottom: 16,
    paddingHorizontal: 16,
  },

  descriptionInput: {
    height: 144,
    borderWidth: 1,
    borderRadius: 12,
    backgroundColor: "#E8EDF2",
    borderColor: "transparent",
    width: "100%",
    marginBottom: 16,
    padding: 16,
  },
  dateBox: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
  },

  priority: {
    flexDirection: "row",
    alignItems: "center",
    justifyContent: "space-between",
    width: "100%",
  },
});

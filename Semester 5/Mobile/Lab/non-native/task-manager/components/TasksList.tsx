import { Task } from "@/domain/Task";
import TaskCard from "./TaskCard";
import { FlatList } from "react-native";

interface TasksListProps {
  tasks: Task[];
}

export default function TasksList({ tasks }: TasksListProps) {
  return (
    <FlatList
      style={{ width: "100%", marginTop: 16, paddingTop: 8 }}
      data={tasks}
      renderItem={({ item }) => <TaskCard task={item} />}
      keyExtractor={(item) => item.taskId}
      showsVerticalScrollIndicator={false}
    />
  );
}

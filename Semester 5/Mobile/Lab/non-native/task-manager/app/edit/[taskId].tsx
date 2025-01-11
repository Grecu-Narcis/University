import { TaskContext } from "@/context/TasksContext";
import { useLocalSearchParams } from "expo-router";
import { useContext } from "react";
import AddOrEdit from "../add_or_edit";

export default function Edit() {
  const tasksContext = useContext(TaskContext)!;
  const { taskId } = useLocalSearchParams();

  const task = tasksContext.getTask(parseInt(taskId as string));

  if (task === undefined) return;

  return <AddOrEdit task={task} />;
}

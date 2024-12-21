export enum TaskPriority {
    HIGH = "High",
    MEDIUM = "Medium",
    LOW = "Low",
  }

export function getPriorityFromString(priorityAsString: string){
  if (priorityAsString == "High")
    return TaskPriority.HIGH

  if (priorityAsString == "Medium")
    return TaskPriority.MEDIUM

  if (priorityAsString == "Low")
    return TaskPriority.LOW

  return TaskPriority.LOW
}
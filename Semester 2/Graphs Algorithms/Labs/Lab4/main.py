from domain.directed_graph import *
from ui.ui import UI


graph = read_graph_from_file_1('graph.txt')

ui = UI()
ui.main_menu()

graph = read_activities("activities.txt")
write_graph_to_file("demo.txt", graph)

sorted_graph = topological_sort_graph(graph)
print(sorted_graph)

graph.compute_activities_times()

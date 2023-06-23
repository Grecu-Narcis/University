from ui.ui import UI

from domain.undirected_graph import *
from domain.directed_graph import *


def main():
    graph = read_directed_graph_from_file_1("graph.txt")
    for component in get_strongly_connected_components(graph):
        print(component)


ui = UI()
ui.main_menu()
#main()

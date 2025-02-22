public class Main {
    public static void main(String[] args) {
        Graph g = new Graph(8);

        g.addEdge(0, 1);
        g.addEdge(0, 2);

        g.addEdge(1, 2);
        g.addEdge(1, 3);

        g.addEdge(2, 3);

        g.addEdge(3, 4);
        g.addEdge(3, 5);

        g.addEdge(4, 5);
        g.addEdge(4, 6);

        g.addEdge(5, 6);
        g.addEdge(5, 7);

        g.addEdge(6, 7);

//        Graph g1 = Graph.generateGraph(12, 50);

        GraphColoring graphColoring = new GraphColoring(g);

        graphColoring.colorGraph(10);
    }
}

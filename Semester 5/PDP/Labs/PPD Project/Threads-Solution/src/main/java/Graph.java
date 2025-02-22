import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Graph {
    private final List<List<Integer>> edges;
    private final int nodes;

    public Graph(int nodes) {
        this.nodes = nodes;

        this.edges = new ArrayList<>();

        for (int i = 0; i < this.nodes; i++)
            this.edges.add(new ArrayList<>());
    }

    public static Graph generateGraph(int nodes, int edges) {
        Graph generatedGraph = new Graph(nodes);
        Random random = new Random();

        while (edges > 0) {
            int x = random.nextInt(nodes);
            int y = random.nextInt(nodes);

            if (generatedGraph.isEdge(x, y))
                continue;

            generatedGraph.addEdge(x, y);
            edges--;
        }

        return generatedGraph;
    }

    public void addEdge(int x, int y) {
        if (this.edges.get(x).contains(y))
            return;

        this.edges.get(x).add(y);
        this.edges.get(y).add(x);
    }

    public boolean isEdge(int x, int y) {
        return this.edges.get(x).contains(y);
    }

    public List<Integer> getNeighbours(int x) {
        return this.edges.get(x);
    }

    public int getNodesCount() {
        return this.nodes;
    }
}

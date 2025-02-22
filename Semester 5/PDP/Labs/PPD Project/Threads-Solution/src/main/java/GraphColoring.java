import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;

public class GraphColoring {
    private final Graph graph;
    private final Map<Integer, Integer> colors;
    private final List<ReentrantLock> locks;

    public GraphColoring(Graph graph) {
        this.graph = graph;
        this.colors = new HashMap<>();
        this.locks = new ArrayList<>();
        for (int i = 0; i < this.graph.getNodesCount(); i++)
            this.locks.add(new ReentrantLock());
    }

    public int findColor(int node) {
        for (int color = 0; color < this.graph.getNodesCount(); color++)
        {
            boolean isUsed = false;

            for (var neigh : this.graph.getNeighbours(node))
                if (this.colors.getOrDefault(neigh,-1).equals(color))
                    isUsed = true;

            if (!isUsed)
                return color;
        }

        return -1;
    }

    public List<Integer> getLocksIndexes(int node) {
        List<Integer> locksIndexes = new ArrayList<>();
        locksIndexes.add(node);

        locksIndexes.addAll(this.graph.getNeighbours(node));

        Collections.sort(locksIndexes);

        return locksIndexes;
    }

    public void colorWorker(int workerId, int numberOfWorkers) {
        int numberOfNodesPerWorker = this.graph.getNodesCount() / numberOfWorkers;

        if (numberOfNodesPerWorker == 0 && workerId >= this.graph.getNodesCount())
            return;

        if (numberOfNodesPerWorker == 0) numberOfNodesPerWorker = 1;

        int start = workerId * numberOfNodesPerWorker;
        int end = workerId == this.graph.getNodesCount() - 1 || workerId == numberOfWorkers - 1
            ? this.graph.getNodesCount() : start + numberOfNodesPerWorker;

        for (int i = start; i < end; i++)
        {
            List<Integer> locksIndexes = this.getLocksIndexes(i);

            for (int lockIndex : locksIndexes)
                this.locks.get(lockIndex).lock();

            int color = this.findColor(i);
            this.colors.put(i, color);

            Logger.log("Thread " + workerId + " coloring node: " + i + " with color: " + color);

            for (int lockIndex : locksIndexes)
                this.locks.get(lockIndex).unlock();
        }
    }

    public void colorGraph(int numberOfWorkers) {
        try (ExecutorService executorService = Executors.newFixedThreadPool(numberOfWorkers)) {
            for (int i = 0; i < numberOfWorkers; i++) {
                int finalI = i;
                executorService.submit(() -> colorWorker(finalI, numberOfWorkers));
            }
        }
    }
}

package No3_Concurrency_Programming_with_Java.cp3.paralle;

import No3_Concurrency_Programming_with_Java.cp3.Classifier;
import No3_Concurrency_Programming_with_Java.cp3.model.Distance;
import No3_Concurrency_Programming_with_Java.cp3.model.Sample;

import java.util.*;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class KnnClassifierParallelGroup implements Classifier {
    //并发版本二
    //平均分配任务到每个核心上
    private final List<? extends Sample> dataSet;
    private final int k;
    private final ThreadPoolExecutor executor;
    private final int numThreads;
    private final boolean parallelSort;

    public KnnClassifierParallelGroup(List<? extends Sample> dataSet,
                                      int k, int factor,
                                      boolean parallelSort) {
        this.dataSet = dataSet;
        this.k = k;
        numThreads = factor * (Runtime.getRuntime().availableProcessors());
        executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(numThreads);
        this.parallelSort = parallelSort;
    }

    public String classify(Sample example) throws Exception {
        Distance[] distances = new Distance[dataSet.size()];
        CountDownLatch endController = new CountDownLatch(numThreads);

        int length = dataSet.size() / numThreads;
        int startIndex = 0, endIndex = length;
        for (int i = 0; i < numThreads; i++) {
            GroupDistanceTask task = new GroupDistanceTask(distances, startIndex,
                    endIndex, dataSet, example, endController);
            startIndex = endIndex;
            if (i < numThreads - 2) {
                endIndex = endIndex + length;
            } else {
                endIndex = dataSet.size();
            }
            executor.execute(task);
        }
        return getString(distances, endController, parallelSort, k, dataSet);

    }

    static String getString(Distance[] distances, CountDownLatch endController, boolean parallelSort, int k, List<? extends Sample> dataSet) throws InterruptedException {
        endController.await();
        if (parallelSort) {
            Arrays.parallelSort(distances);
        } else {
            Arrays.sort(distances);
        }
        Map<String, Integer> results = new HashMap<>();
        for (int i = 0; i < k; i++) {
            Sample localExample = dataSet.get(distances[i].getIndex());
            String tag = localExample.getTag();
            results.merge(tag, 1, Integer::sum);
        }
        return Collections.max(results.entrySet(), Map.Entry.comparingByValue()).getKey();
    }

    public void destroy() {
        executor.shutdown();
    }
}

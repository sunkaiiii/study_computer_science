package No3_Concurrency_Programming_with_Java.cp3.paralle;

import No3_Concurrency_Programming_with_Java.cp3.Classifier;
import No3_Concurrency_Programming_with_Java.cp3.model.Distance;
import No3_Concurrency_Programming_with_Java.cp3.model.Sample;
import No3_Concurrency_Programming_with_Java.cp3.seriel.IndividualDistanceTask;

import java.util.*;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

import static No3_Concurrency_Programming_with_Java.cp3.paralle.KnnClassifierParallelGroup.getString;

public class KnnClassifierParallelIndividual implements Classifier {
    //并发版本一
    //为每一个训练集生成一个分组任务
    private final List<? extends Sample> dataSet;
    private final int k;
    private final ThreadPoolExecutor executor;
    private final int numThreads;
    private final boolean parallelSort;

    public KnnClassifierParallelIndividual(List<? extends Sample> dataSet,
                                           int k, int factor,
                                           boolean parallelSort) {
        this.dataSet = dataSet;
        this.k = k;
        numThreads = factor * (Runtime.getRuntime().availableProcessors());
        executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(numThreads);
        this.parallelSort = parallelSort;
    }

    //在这个方法中，使用CountDownLath类还进行同步。
    //将需要计算的距离创建一个任务，并将其发送给执行器
    public String classify(Sample example) throws Exception {
        Distance[] distances = new Distance[dataSet.size()];
        CountDownLatch endController = new CountDownLatch(dataSet.size()); //给数据集一样大小的计数数字
        int index = 0;
        for (Sample localExample : dataSet) {
            IndividualDistanceTask task = new IndividualDistanceTask(distances, index, localExample, example, endController);
            executor.execute(task);
            index++;
        }
        return getString(distances, endController, parallelSort, k, dataSet);
    }

    public void destroy() {
        executor.shutdown();
    }
}

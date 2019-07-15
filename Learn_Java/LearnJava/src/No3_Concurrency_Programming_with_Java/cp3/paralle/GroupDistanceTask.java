package No3_Concurrency_Programming_with_Java.cp3.paralle;

import No3_Concurrency_Programming_with_Java.cp3.model.Distance;
import No3_Concurrency_Programming_with_Java.cp3.model.Sample;
import No3_Concurrency_Programming_with_Java.cp3.seriel.EuclideanDistanceCalculator;

import java.util.List;
import java.util.concurrent.CountDownLatch;

public class GroupDistanceTask implements Runnable {
    private final Distance[] distances;
    private final int startIndex, endIndex;
    private final Sample example;
    private final List<? extends Sample> dataSet;
    private final CountDownLatch endController;

    public GroupDistanceTask(Distance[] distances, int startIndex,
                             int endIndex, List<? extends Sample> dataSet,
                             Sample example, CountDownLatch endController) {
        this.distances = distances;
        this.startIndex = startIndex;
        this.endIndex = endIndex;
        this.example = example;
        this.dataSet = dataSet;
        this.endController = endController;
    }

    @Override
    public void run() {
        for (int index = startIndex; index < endIndex; index++) {
            Sample localExample = dataSet.get(index);
            distances[index] = new Distance();
            distances[index].setIndex(index);
            distances[index].setDistance(EuclideanDistanceCalculator
                    .calculate(localExample, example));
        }
        endController.countDown();
    }
}

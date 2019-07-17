package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.paralle;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.Classifier;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.model.Distance;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.model.Sample;
import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp3.seriel.EuclideanDistanceCalculator;

import java.util.*;

public class KnnClassfier implements Classifier {
    //串形版本的k-mean算法
    private final List<? extends Sample> dataSet;
    private int k;

    public KnnClassfier(List<? extends Sample> dataSet, int k) {
        this.dataSet = dataSet;
        this.k = k;
    }

    public String classify(Sample example) {
        //方法会返回一个字符串
        //其中含有要指派给该实例的标签
        Distance[] distances = new Distance[dataSet.size()];
        int index = 0;

        for (Sample localExample : dataSet) {
            distances[index] = new Distance();
            distances[index].setIndex(index);
            distances[index].setDistance(EuclideanDistanceCalculator.calculate(localExample, example));
            index++;
        }
        Arrays.sort(distances);
        Map<String, Integer> results = new HashMap<>();
        for (int i = 0; i < k; i++) {
            Sample localExample = dataSet.get(distances[i].getIndex());
            String tag = localExample.getTag();
            results.merge(tag, 1, (a, b) -> a + b);
        }
        return Collections.max(results.entrySet(), Map.Entry.comparingByValue()).getKey();

    }
}

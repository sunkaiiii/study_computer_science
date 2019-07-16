package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.paralle;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.find_string.basic.BestMatchingData;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadPoolExecutor;

public class BestMatchingBasicConcurrentCalculation {
    //并发检索的第一个版本
    public static BestMatchingData getBestMatchingWords(String
                                                                word, List<String> dictionary) throws InterruptedException,
            ExecutionException {
        int numCores = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor executor = (ThreadPoolExecutor)
                Executors.newFixedThreadPool(numCores);
        int size = dictionary.size();
        int step = size / numCores;
        int startIndex, endIndex;
        List<Future<BestMatchingData>> results = new ArrayList<>();
        for (int i = 0; i < numCores; i++) {
            startIndex = i * step;
            if (i == numCores - 1) {
                endIndex = dictionary.size();
            } else {
                endIndex = (i + 1) * step;
            }
            BestMatchingBasicTask task = new BestMatchingBasicTask(startIndex,
                    endIndex, dictionary, word);
            Future future = executor.submit(task);
            results.add(future);
        }
        executor.shutdown(); //将任务发送给执行器后，可以使用shutdown方法来结束执行
        List<String> words = new ArrayList<String>();
        int minDistance = Integer.MAX_VALUE;
        for (Future<BestMatchingData> future : results) {
            BestMatchingData data = future.get(); //如果任务执行结束，会通过自定义的Call方法返回需要的对象
            if (data.getDistance() < minDistance) {
                words.clear();
                minDistance = data.getDistance(); //如果某一个任务耗时太久，就需要一直等着。并发完整度不是特别高
                words.addAll(data.getWords());
            } else if (data.getDistance() == minDistance) {
                words.addAll(data.getWords());
            }
        }
        BestMatchingData result = new BestMatchingData();
        result.setDistance(minDistance);
        result.setWords(words);
        return result;
    }
}

package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.parallel;

import No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp5.textIndexing.basic.Document;

import java.io.File;
import java.util.Date;
import java.util.concurrent.*;

public class ConcurrentIndexing {
    //并行版本1的主类
    //创建并启动所有的组建，等待执行过程结束
    public static void startParalleVersion1() {
        int numCores = Runtime.getRuntime().availableProcessors();
        ThreadPoolExecutor executor = (ThreadPoolExecutor)
                Executors.newFixedThreadPool(Math.max(numCores - 1, 1));
        ExecutorCompletionService<Document> completionService = new
                ExecutorCompletionService<>(executor);
        ConcurrentHashMap<String, ConcurrentLinkedDeque<String>>
                invertedIndex = new ConcurrentHashMap
                <>();
        Date start, end;
        File source = new File("data");
        File[] files = source.listFiles();
        start = new Date();
        for (File file : files) {
            IndexingTask task = new IndexingTask(file);
            completionService.submit(task);
            if (executor.getQueue().size() > 1000) {
                do {
                    try {
                        TimeUnit.MILLISECONDS.sleep(50);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } while (executor.getQueue().size() > 1000);
            }
        }
        InvertedIndexTask invertedIndexTask = new InvertedIndexTask
                (completionService, invertedIndex);
        Thread thread1 = new Thread(invertedIndexTask);
        thread1.start();
        InvertedIndexTask invertedIndexTask2 = new InvertedIndexTask
                (completionService, invertedIndex);
        Thread thread2 = new Thread(invertedIndexTask2);
        thread2.start();
        executor.shutdown();
        try {
            executor.awaitTermination(1, TimeUnit.DAYS);
            thread1.interrupt();
            thread2.interrupt();
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        end = new Date();
        System.out.println("Execution Time: " + (end.getTime() -
                start.getTime()));
        System.out.println("invertedIndex: " + invertedIndex.size());
    }
}

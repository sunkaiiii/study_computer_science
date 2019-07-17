package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp2;

import java.io.File;
import java.util.concurrent.ConcurrentLinkedQueue;

public class ParallelGroupFileSearch {
    //并行搜索文件的执行类
    //所有的线程会共享一个队列。
    public static void searchFiles(File file, String fileName, Result paralleResult) {
        ConcurrentLinkedQueue<File> directories = new ConcurrentLinkedQueue<>();
        File[] contents = file.listFiles();
        for (File content : contents) {
            if (content.isDirectory()) {
                directories.add(content);
            }
        }
        //获取处理器的数量
        int numThreads = Runtime.getRuntime().availableProcessors();
        Thread[] threads = new Thread[numThreads];
        ParalleGroupFileTask[] task = new ParalleGroupFileTask[numThreads];

        for (int i = 0; i < numThreads; i++) {
            task[i] = new ParalleGroupFileTask(fileName, paralleResult, directories);
            threads[i] = new Thread(task[i]);
            threads[i].start();
        }
        boolean finish = false;
        int numFinished = 0;
        while (!finish) {
            numFinished = 0;
            for (int i = 0; i < threads.length; i++) {
                if (threads[i].getState() == Thread.State.TERMINATED) {
                    numFinished++;
                    if (task[i].getFound()) {
                        finish = true;
                    }
                }
            }
            if (numFinished == threads.length) {
                finish = true;
            }
        }
        if (numFinished != threads.length) { //扫尾，因为已经找到文件，结束掉所有线程
            for (Thread thread : threads) {
                thread.interrupt();
            }
        }
    }
}

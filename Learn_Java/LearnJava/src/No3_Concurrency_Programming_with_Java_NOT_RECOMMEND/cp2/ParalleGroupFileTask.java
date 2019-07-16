package No3_Concurrency_Programming_with_Java_NOT_RECOMMEND.cp2;

import java.io.File;
import java.util.concurrent.ConcurrentLinkedQueue;

public class ParalleGroupFileTask implements Runnable {
    //并行搜索文件
    private final String fileName;
    private final ConcurrentLinkedQueue<File> directories;
    private final Result paralleResult;
    private boolean found;

    public ParalleGroupFileTask(String fileName, Result paralleResult, ConcurrentLinkedQueue<File> directories) {
        this.fileName = fileName;
        this.paralleResult = paralleResult;
        this.directories = directories;
        this.found = false;
    }

    @Override
    public void run() {
        //run方法有一个循环，在队列中有元素且没有找到该文件时会被执行
        //他会调用ConcurrentLinkedQueue类的poll()方法处理下一个目录
        //并调用辅助方法processDirectory
        while (directories.size() > 0) {
            File file = directories.poll();
            try {
                processDirectory(file, fileName, paralleResult);
                if (found) {
                    System.out.printf("%s has found the file%n", Thread.currentThread().getName());
                    System.out.printf("Parallel Search: Path:%s%n", paralleResult.getPath());
                    return;
                }
            } catch (InterruptedException e) {
                System.out.printf("%s has been interuupted%n", Thread.currentThread().getName());
            }
        }
    }

    private void processDirectory(File file, String fileName, Result paralleResult) throws InterruptedException {
        //接受待处理的File对象
        //通过ListFile获取对象内容
        File[] contents = file.listFiles();
        if ((contents == null) || (contents.length == 0)) {
            return;
        }

        for (File content : contents) {
            if (content.isDirectory()) {
                processDirectory(content, fileName, paralleResult);
            }
            if (Thread.currentThread().isInterrupted()) {
                throw new InterruptedException();
            }
            if (found) {
                return;
            } else {
                processFile(content, fileName, paralleResult);
                if (Thread.currentThread().isInterrupted()) {
                    throw new InterruptedException();
                }
                if (found) {
                    return;
                }
            }

        }
    }

    private void processFile(File content, String fileName, Result paralleResult) {
        //判断是不是所需文件
        if (content.getName().equals(fileName)) {
            paralleResult.setPath(content.getAbsolutePath());
            this.found = true;
            paralleResult.setFound(true);
        }
    }

    public boolean getFound() {
        return found;
    }
}

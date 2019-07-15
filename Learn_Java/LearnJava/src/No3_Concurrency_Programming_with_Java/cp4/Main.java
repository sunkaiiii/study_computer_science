package No3_Concurrency_Programming_with_Java.cp4;

import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) {
        // 创建system 并将其作为一个线程执行
        NewsSystem system = new NewsSystem("data\\sources.txt"); //作者Github的项目里并没有提供这个文件……
        Thread t = new Thread(system);
        t.start();
        // 等待10 分钟
        try {
            TimeUnit.MINUTES.sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        // 通知system 终止
        system.shutdown();
    }
}

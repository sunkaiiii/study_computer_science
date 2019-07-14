package No3_Concurrency_Programming_with_Java.cp2;

import java.util.ArrayList;
import java.util.List;

public class ParallelIndividualMultiplier {
    //第一个并行版本的执行类
    //接受将要相乘的矩阵作为参数。
    //并创建一个单独的IndividualMultiplierTask来计算每个元素
    //每10个一组的方式启动线程。
    //启动完毕后，可使用waitForThreads辅助方法等待这10个线程最终完成
    public static void multiply(double[][] matrix1, double[][] matrix2,
                                double[][] result) {
        List<Thread> threads=new ArrayList<>();
        int rows1=matrix1.length;
        int rows2=matrix2.length;
        for (int i=0; i<rows1; i++) {
            for (int j=0; j<rows2; j++) {
                IndividualMultiplierTask task=new IndividualMultiplierTask
                        (result, matrix1, matrix2, i, j);
                Thread thread=new Thread(task);
                thread.start();
                threads.add(thread);
                if (threads.size() % 10 == 0) {
                    waitForThreads(threads);
                }
            }
        }
    }
    private static void waitForThreads(List<Thread> threads){
        for (Thread thread: threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        threads.clear();
    }
}

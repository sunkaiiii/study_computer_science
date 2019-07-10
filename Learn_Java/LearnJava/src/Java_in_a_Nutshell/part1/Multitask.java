package Java_in_a_Nutshell.part1;

//一种所谓"优雅结束"模式
public class Multitask implements Runnable {
    private volatile boolean shutdown=false;

    //只要没有其他线程调用shutdown方法，处理中的线程就会继续处理任务
    //而且状态是同步的。
    public void shutdown(){
        shutdown=true;
    }

    @Override
    public void run(){
        while (!shutdown){
            //...处理其他任务
        }
    }
}

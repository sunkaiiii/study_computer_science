import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by sunkai on 2017/12/20
 */

//使用阻塞队列实现一个简单的生产者消费者模式
public class BlockQueueTest {
    public static void main(String[] args){
        Queue<String> queue=new BlockingQueue2<>(10);
        Producer producer=new Producer(queue);
        Comsumer comsumer=new Comsumer(queue);
        new Thread(producer).start();
        new Thread(comsumer).start();
    }
}

class Producer implements Runnable{
    Queue<String> queue;
    public Producer(Queue<String> queue){
        this.queue=queue;
    }

    @Override
    public void run() {
        int i=0;
        while(true){
            try{
//                Thread.sleep(500);
                queue.enqueue("产品"+i);
                ++i;
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
}

class Comsumer implements Runnable{
    Queue<String> queue;
    public Comsumer(Queue<String> queue){
        this.queue=queue;
    }

    @Override
    public void run() {
        while(true)
        {
            try {
//                Thread.sleep(6000);
                queue.deque();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
}

interface Queue<T>{
    void enqueue(T t) throws InterruptedException;
    T deque() throws InterruptedException;
}

//使用sychronized，wait，notifyall实现的等待以及唤醒的类
class BlockQueue<T> implements Queue<T>{
    private List<T> queue=new LinkedList<>();
    private int limit;
    public BlockQueue(int limit){
        this.limit=limit;
    }

    @Override
    public synchronized void enqueue(T t) throws InterruptedException {
        while(queue.size()==limit)
            wait();
        if(queue.size()==0)
            notifyAll();
        queue.add(t);
        System.out.println(t+"被放入");
    }

    @Override
    public synchronized T deque() throws InterruptedException {
        while(queue.size()==0)
            wait();
        if(queue.size()==limit)
            notifyAll();
        T t=queue.remove(0);
        System.out.println(t+"被取出");
        return t;
    }
}

class BlockingQueue2<T> implements Queue<T>{
    private List<T> queue=new LinkedList<>();
    private int limit;
    private ReentrantLock lock;
    public BlockingQueue2(int limit){
        this.limit=limit;
        lock=new ReentrantLock(false);
    }

    @Override
    public void enqueue(T t) throws InterruptedException {
        ReentrantLock lock=this.lock;
        lock.lock();
        try{
            if(queue.size()!=limit){
                queue.add(t);
                System.out.println(t+"被放入");
            }
        }finally {
            lock.unlock();
        }
    }

    @Override
    public T deque() throws InterruptedException {
        ReentrantLock lock=this.lock;
        lock.lock();
        T t=null;
        try{
            if(queue.size()>0) {
                t = queue.remove(0);
                System.out.println(t+"被取出");
            }
        }finally {
            lock.unlock();
        }
        return t;
    }
}
import java.util.Random;

/**
 * Created by sunkai on 2017/9/20
 */
public class ProducerConsumer {
    static final int N=100;//定义缓冲区大小的常量
    static producer p=new producer(); //初始化一个新的生产者线程
    static consumer c=new consumer(); //初始化一个新的消费者线程
    static our_monitor mon=new our_monitor(); //初始化一个新的管程

    public static void main(String args[]){
        p.start();
        c.start();
    }

    static class producer extends Thread{
        public void run(){//run方法包含了线程代码
            int item;
            while(true) {//生产者循环
                item=produce_item();
                mon.insert(item);
//                try{
//                    sleep(800);
//                }
//                catch (InterruptedException e)
//                {
//                    e.printStackTrace();
//                }
            }
        }
        private int produce_item(){
            Random random=new Random();
            int val=random.nextInt();
            System.out.println("生产了："+val);
            return val;
        }
    }
    static class consumer extends Thread{
        public void run(){//run方法包含了线程代码
            int item;
            while(true) {//消费者循环
                item = mon.remove();
//                try{
//                    sleep(800);
//                }
//                catch (InterruptedException e)
//                {
//                    e.printStackTrace();
//                }
                consume_item(item);
            }
        }
        private void consume_item(int item){//实际消费
            System.out.println("消费了:"+item);
        }
    }
    static class our_monitor{//这是一个管程
        private int buffer[]=new int[N];
        private int count=0,lo=0,hi=0;
        public synchronized void insert(int val){
            if(count==N)
                go_to_sleep();//如果缓冲区满，则进入睡眠
            buffer[hi]=val;//向缓冲区中插入一个新的数据项
            hi=(hi+1)%N;//设置下一个数据项的槽
            count=count+1;//缓冲区中的数据项又多了一项
            if(count==1)//如果消费者在休眠，则将其唤醒
                notify();
        }
        public synchronized int remove(){
            int val;
            if(count==0)//如果缓冲区为空，进入休眠
                go_to_sleep();
            val=buffer[lo];//从缓冲区中取出一个数据项
            lo=(lo+1)%N;//设置待取数据项的槽
            count=count-1;
            if(count==N-1)//如果生产者在休眠，则将其唤醒
                notify();
            return val;
        }
        private void go_to_sleep(){
            try{
                wait();
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }

}

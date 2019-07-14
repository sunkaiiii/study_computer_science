package No1_Java_in_a_Nutshell.part1;

import java.util.LinkedList;

//简化的线程安全的队列
//一个线程调用push方法
//另一个线程调用pop方法
//如果没有数据，pop方法等待，直到有数据
public class WaitingQueue<E> {
    LinkedList<E> q=new LinkedList<>();
    public synchronized void push(E o){
        q.add(o);
        this.notifyAll();
    }
    public synchronized E pop(){
        while(q.size()==0){
            try{
                this.wait();
            }catch (InterruptedException ignore){}
        }
        return q.remove();
    }
}

package StackAndQueue;

import StackAndQueue.Queue;
import StackAndQueue.Stack;

import java.util.Iterator;

public class StackAndQueueTest {
    public static class  Stopwatch{
        private final long start;
        public Stopwatch(){
            start=System.currentTimeMillis();
        }
        public double elapsedTime(){
            long now=System.currentTimeMillis();
            return (now-start)/1000.0;
        }
    }
    public static void main(String args[]){
        Stack<Integer> testStack=new Stack<>();
        testStack.push(1);
        testStack.push(2);
        testStack.push(3);
        Stopwatch timer=new Stopwatch();
        System.out.println(testStack.size());
        System.out.println(testStack.pop());
        System.out.println("测试迭代foreach");
        for(int s:testStack){
            System.out.println(s);
        }
        System.out.println("测试迭代while");
        Iterator<Integer> i=testStack.iterator();
        while(i.hasNext()){
            System.out.println(i.next());
        }
        System.out.println("测试队列");
        Queue<Integer> testQueue=new Queue<>();
        testQueue.enqueue(1);
        testQueue.enqueue(2);
        testQueue.enqueue(3);
        System.out.println(testQueue.size());
        System.out.println(testQueue.dequeue());
        System.out.println("测试迭代foreach");
        for(int s:testQueue){
            System.out.println(s);
        }
        System.out.println("测试迭代while");
        Iterator<Integer> i2=testQueue.iterator();
        while(i2.hasNext()){
            System.out.println(i2.next());
        }
        System.out.println("用时"+timer.elapsedTime());
    }
}

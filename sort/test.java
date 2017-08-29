package sort;

import StackAndQueue.StackAndQueueTest;

import java.util.Arrays;
import java.util.Random;

public class test {
    public static double time(String alg,Comparable[] a){
        StackAndQueueTest.Stopwatch timer=new StackAndQueueTest.Stopwatch();
        if(alg.equals("Insertion"))
            Insertion.sort(a);
        else if(alg.equals("Shell"))
            Shell.sort(a);
        else if(alg.equals("Merge"))
            Merge.sort(a);
        else if(alg.equals("Quick"))
            Quick.sort(a);
        else if(alg.equals("Improved_Merge"))
            Improved_Merge.sort(a);
        else if(alg.equals("Heap"))
            Heap.sort(a);
        else if(alg.equals("Array_Sort"))
            Arrays.sort(a);
        return timer.elapsedTime();
    }
    public static double timeRandomInput(String alg,Comparable[] a){
        double total=0.0;
        total+=time(alg,a);
        return total;
    }
    public static void main(String[] args){
//        System.out.println("Insertion:"+timeRandomInput("Insertion",500000,1));
        Random random=new Random();
        Integer[] a=new Integer[40000000];
        for(int i=0;i<40000000;i++){
            a[i]=random.nextInt(40000000);
        }
        Integer[] b=new Integer[40000000];
        for(int i=0;i<40000000;i++){
            b[i]=a[i];
        }
//        System.out.println("Shell:"+timeRandomInput("Shell",b));
        for(int i=0;i<40000000;i++){
            b[i]=a[i];
        }
        System.out.println("归并:"+timeRandomInput("Merge",b));
        for(int i=0;i<40000000;i++){
            b[i]=a[i];
        }
        System.out.println("改进的归并:"+timeRandomInput("Improved_Merge",b));
////        System.out.println("Quick:"+timeRandomInput("Quick",a));
        for(int i=0;i<40000000;i++){
            b[i]=a[i];
        }
        System.out.println("堆排序:"+timeRandomInput("Heap",b));
        for(int i=0;i<40000000;i++){
            b[i]=a[i];
        }
        System.out.println("Java库自带排序:"+timeRandomInput("Array_Sort",b));

//        Integer a2[]={9,8,7,6,5,4,3,2,1};
//        Improved_Merge.sort(a2);

//        PriorityQueue<String> a=new PriorityQueue<>(11);
//        a.insert("T");
//        a.insert("S");
//        a.insert("R");
//        a.insert("P");
//        a.insert("N");
//        a.insert("O");
//        a.insert("A");
//        a.insert("E");
//        a.insert("I");
//        a.insert("H");
//        a.insert("G");
//        a.show();
//        PriorityQueue<Integer> b=new PriorityQueue<>(5);
//        b.insert(5);
//        b.insert(1);
//        b.insert(2);
//        b.insert(3);
//        b.insert(4);
//        b.show();

//        Integer a[]={7,6,5,4,3,1,2,8,9,10};
//        Heap.sort(a);
    }
}

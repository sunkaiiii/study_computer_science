package sort;

import StackAndQueue.StackAndQueueTest;
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
//        System.out.println("Shell:"+timeRandomInput("Shell",a));
        System.out.println("Merge:"+timeRandomInput("Merge",a));
        System.out.println("Improved_Merge:"+timeRandomInput("Improved_Merge",a));
//        System.out.println("Quick:"+timeRandomInput("Quick",a));
//        Integer a2[]={9,8,7,6,5,4,3,2,1};
//        Improved_Merge.sort(a2);
    }
}

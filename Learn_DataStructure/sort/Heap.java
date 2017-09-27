package sort;

import java.security.Key;

public class Heap{
    private static int N = 0;
    public static void sort(Comparable[] a){
        N=a.length;
        Comparable[] b=new Comparable[a.length+1];
        for(int i=1;i<=a.length;i++){
            b[i]=a[i-1];
        }
        for(int k=N/2;k>=1;k--){
            sink(b,k,N);
        }
        while(N>1)
        {
            exch(b,1,N--);
            sink(b,1,N);
        }
        N=a.length;
//        show(b);
    }
    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    private static boolean less(Comparable[] a,int i,int j){
        return a[i].compareTo(a[j])<0;
    }
    private static void exch(Comparable[] a,int i,int j){
        Comparable t=a[i];
        a[i]=a[j];
        a[j]=t;
    }
    private static void sink(Comparable[]a,int k,int N){
        while(2*k<=N){
            int j=2*k;
            if(j<N&&less(a,j,j+1))
                j++;
            if(!less(a,k,j))
                break;
            exch(a,k,j);
            k=j;
        }
    }
    private static void show(Comparable[] a){
        for(int i=1;i<=N;i++){
            System.out.println(a[i]);
        }
    }
}

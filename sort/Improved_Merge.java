package sort;

public class Improved_Merge {
    private static Comparable[] aux;
    private static int m=5;
    public static void sort(Comparable[] a) {
        aux=new Comparable[a.length];
        sort(a,0,a.length-1);
//        show(a);
    }
    private static void sort(Comparable[] a,int lo,int hi){
        if(hi<=lo+m){
            Insertion.sort(a,lo,hi);
            return;
        }
        int mid=lo+(hi-lo)/2;
        sort(a,lo,mid);
        sort(a,mid+1,hi);
        merge(a,lo,mid,hi);
    }
    private static void merge(Comparable[] a,int lo,int mid,int hi){
        int i=lo;
        int j=mid+1;
        for(int k=lo;k<=hi;k++){
            aux[k]=a[k];
        }
        for(int k=lo;k<=hi;k++){
            if(i>mid)
                a[k]=aux[j++];
            else if(j>hi)
                a[k]=aux[i++];
            else if(less(aux[j],aux[i]))
                a[k]=aux[j++];
            else
                a[k]=aux[i++];
        }
//        show(a);
    }

    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    private static void exch(Comparable[] a, int i, int j) {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }

    private static boolean isSorted(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            if (less(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }
}

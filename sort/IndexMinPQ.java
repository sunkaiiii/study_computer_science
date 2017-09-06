package sort;

/**
 * Created by sunkai on 2017/9/6
 */
public class IndexMinPQ<Key extends Comparable<Key>> {
    private Key[] pq;
    Key[] index;
    private int N = 0;

    public IndexMinPQ(int maxN) {
        pq = (Key[]) new Comparable[maxN + 1];
        index=(Key[])new Comparable[maxN+1];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void insert(int index,Key v) {
        pq[++N] = v;
        this.index[index]=v;
        swim(N);
    }

    public int delMin() {
        Key min = pq[1];
        exch(1, N--);
        pq[N + 1] = null;
        sink(1);
        for(int i=0;i<index.length;i++){
            if(index[i].equals(min)){
                return i;
            }
        }
        return -1;
    }
    public boolean contians(int i){
        if(index[i]==null)
            return true;
        return false;
    }
    public void change(int i,Key key){
        index[i]=key;
    }
    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) > 0;
    }

    private void exch(int i, int j) {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }

    private void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            exch(k / 2, k);
            k = k / 2;
        }
    }

    private void sink(int k) {
        while (2 * k <= N) {
            int j = 2 * k;
            if (j < N && less(j, j + 1))
                j++;
            if (!less(k, j))
                break;
            exch(k, j);
            k = j;
        }
    }

    public void show() {
        for (int i = 1; i <= N; i++) {
            System.out.println(pq[i]);
        }
    }
}

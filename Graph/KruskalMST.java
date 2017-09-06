package Graph;

import StackAndQueue.Queue;
import sort.MinPQ;
import unionFind.UF;
import unionFind.WeightedQuickUnionUF;

/**
 * Created by sunkai on 2017/9/6
 */
public class KruskalMST {
    private Queue<Edge> mst;
    public KruskalMST(EdgeWeightedGraph G){
        mst=new Queue<Edge>();
        MinPQ<Edge> pq=new MinPQ<Edge>(G.E());
        for(Edge e:G.edges()){
            pq.insert(e);
        }
        WeightedQuickUnionUF uf=new WeightedQuickUnionUF((G.V()));
        while(!pq.isEmpty()&&mst.size()<G.V()-1){
            Edge e=pq.delMin();
            int v=e.either();
            int w=e.other(v);
            if(uf.connected(v,w))
                continue;;
            uf.union(v,w);
            mst.enqueue(e);
        }
    }
    public Iterable<Edge> edges(){
        return mst;
    }
}

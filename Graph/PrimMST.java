package Graph;

import sort.IndexMinPQ;
import sort.MinPQ;

/**
 * Created by sunkai on 2017/9/6
 */
public class PrimMST {
    public Edge[] edgeTo;
    private double[] distTO;
    private boolean[] marked;
    private IndexMinPQ<Double> pq;

    public PrimMST(EdgeWeightedGraph G){
        edgeTo=new Edge[G.V()];
        distTO=new double[G.V()];
        marked=new boolean[G.V()];
        for(int v=0;v<G.V();v++){
            distTO[v]=Double.POSITIVE_INFINITY;
        }
        pq=new IndexMinPQ<>(G.V());
        distTO[0]=0.0;
        pq.insert(0,0.0);
        while (!pq.isEmpty()){
            visit(G,pq.delMin());
        }
    }
    private void visit(EdgeWeightedGraph G,int v){
        marked[v]=true;
        for(Edge e:G.adj(v)){
            int w=e.other(v);
            if(marked[w])
                continue;;
            if(e.weight()<distTO[w]){
                edgeTo[w]=e;
                distTO[w]=e.weight();
                if(pq.contians(w))
                    pq.change(w,distTO[w]);
                else
                    pq.insert(w,distTO[w]);
            }
        }
    }

}

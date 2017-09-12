package Graph;

import StackAndQueue.Stack;
import sort.IndexMinPQ;

/**
 * Created by sunkai on 2017/9/12
 */
public class DijkstraSP {
    private DirectedEdge[] edgeTo;
    private double[] disTo;
    private IndexMinPQ<Double> pq;

    public DijkstraSP(EdgeWeightedDiagraph G,int s){
        edgeTo=new DirectedEdge[G.V()];
        disTo=new double[G.V()];
        pq=new IndexMinPQ<>(G.V());
        for(int v=0;v<G.V();v++)
            disTo[v]=Double.POSITIVE_INFINITY;
        disTo[s]=0.0;
        pq.insert(s,0.0);
        while(!pq.isEmpty())
            relax(G,pq.delMin());
    }
    private void relax(EdgeWeightedDiagraph G,int v){
        for(DirectedEdge e:G.adj(v)){
            int w=e.to();
            if(disTo[w]>disTo[v]+e.weight())
            {
                disTo[w]=disTo[v]+e.weight();
                edgeTo[w]=e;
                if(pq.contians(w))
                    pq.change(w,disTo[w]);
                else
                    pq.insert(w,disTo[w]);
            }
        }
    }
    public double distTo(int v){
        return disTo[v];
    }
    public boolean hasPathTo(int v){
        return disTo[v]<Double.POSITIVE_INFINITY;
    }
    public Iterable<DirectedEdge> pathTo(int v){
        if(!hasPathTo(v))
            return null;
        Stack<DirectedEdge> path=new Stack<DirectedEdge>();
        for(DirectedEdge e=edgeTo[v];e!=null;e=edgeTo[e.from()]){
            path.push(e);
        }
        return path;
    }
}

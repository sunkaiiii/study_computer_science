package Graph;

import StackAndQueue.Queue;
import sort.MinPQ;

/**
 * Created by sunkai on 2017/9/6
 */
public class LazyPrimMST {
    private boolean[] marked;
    private Queue<Edge> mst;
    private MinPQ<Edge> pq;
    public LazyPrimMST(EdgeWeightedGraph G){
        pq=new MinPQ<Edge>(G.E());
        marked=new boolean[G.V()];
        mst=new Queue<Edge>();
        visit(G,0);
        while(!pq.isEmpty()){
            Edge e=pq.delMin(); //获得权重最小的边
            int v=e.either();
            int w=e.other(v);
            if(marked[v]&&marked[w])    //跳过失败的边
                continue;;
            mst.enqueue(e); //将边添加到树中
            if(!marked[v])
                visit(G,v);
            if(!marked[w]){
                visit(G,w);
            }
        }
    }
    private void visit(EdgeWeightedGraph G,int v){
        //标记顶点V并将素有连接V且未被标记的顶点加入pq
        marked[v]=true;
        for(Edge e:G.adj(v)){
            if(!marked[e.other(v)])
                pq.insert(e);
        }
    }
    public Iterable<Edge> edges(){
        return mst;
    }
}

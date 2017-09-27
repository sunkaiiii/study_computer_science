package Graph;

import StackAndQueue.Bag;

/**
 * Created by sunkai on 2017/9/5
 */
public class Diagraph {
    private final int V;
    private int E;
    private Bag<Integer>[] adj;
    public Diagraph(int V){
        this.V=V;
        this.E=0;
        adj=(Bag<Integer>[])new Bag[V];
        for(int v =0;v<V;v++){
            adj[v]=new Bag<>();
        }
    }
    public int V(){
        return V;
    }
    public int E(){
        return E;
    }
    public void addEdge(int v,int w){
        adj[v].add(w);
        E++;
    }
    public Iterable<Integer> adj(int v){
        return adj[v];
    }
    public Diagraph reverse(){
        Diagraph R=new Diagraph(V);
        for(int v=0;v<V;v++){
            for (int w:adj[v]){
                R.addEdge(w,v);
            }
        }
        return R;
    }
    @Override
    public String toString() {
        String s = V + "vertices, " + E + " edges\n";
        for (int v = 0; v < V; v++) {
            s += v + ": ";
            for (int w : this.adj(v)) {
                s += w + " ";
            }
            s += "\n";
        }
        return s;
    }
}

package Graph;

import StackAndQueue.Stack;

/**
 * Created by sunkai on 2017/9/5
 */
public class DirectedCycle {
    private boolean[] marked;
    private int edgeTo[];
    private Stack<Integer> cycle;
    private boolean[] onStack;
    public DirectedCycle(Diagraph G){
        onStack=new boolean[G.V()];
        edgeTo=new int[G.V()];
        marked=new boolean[G.V()];
        for(int v=0;v<G.V();v++){
            if(!marked[v]){
                dfs(G,v);
            }
        }
    }
    private void dfs(Diagraph G,int v){
        onStack[v]=true;
        marked[v]=true;
        for(int w:G.adj(v)){
            if(this.hasCycle())
                return;
            else if(!marked[w]){
                edgeTo[w]=v;
                dfs(G,w);
            }
            else if(onStack[w]){
                cycle=new Stack<>();
                for(int x=v;x!=w;x=edgeTo[x]){
                    cycle.push(x);
                }
                cycle.push(w);
                cycle.push(v);
            }
        }
        onStack[v]=false;
    }
    public boolean hasCycle(){
        return cycle!=null;
    }
    public Iterable<Integer> cycle(){
        return cycle;
    }
}
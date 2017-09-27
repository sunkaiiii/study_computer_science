package Graph;

/**
 * Created by sunkai on 2017/9/5
 */
public class DirectedDFS {
    private boolean[] marked;
    public DirectedDFS(Diagraph G,int s){
        marked=new boolean[G.V()];
        dfs(G,s);
    }
    public DirectedDFS(Diagraph G,Iterable<Integer> sources){
        marked=new boolean[G.V()];
        for(int s:sources){
            if(!marked[s]){
                dfs(G,s);
            }
        }
    }
    private void dfs(Diagraph G,int v){
        marked[v]=true;
        for(int w:G.adj(v)){
            if(!marked[w]){
                dfs(G,w);
            }
        }
    }
    public boolean marked(int v){
        return marked[v];
    }
    public static void main(String args[]){

    }
}

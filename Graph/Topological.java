package Graph;

/**
 * Created by sunkai on 2017/9/5
 */
public class Topological {
    private Iterable<Integer> order;
    public Topological(Diagraph G){
        DirectedCycle cyclefinder=new DirectedCycle(G);
        if(!cyclefinder.hasCycle()){
            DepthFIrstOrder dfs=new DepthFIrstOrder(G);
            order=dfs.reversePost();
        }
    }
    public Iterable<Integer> order(){
        return order;
    }
    public boolean isDAG(){
        return order!=null;
    }
}

package Graph;

import StackAndQueue.Queue;
import StackAndQueue.Stack;

/**
 * Created by sunkai on 2017/9/5
 */
public class DepthFIrstOrder {
    private boolean[] marked;
    private Queue<Integer> pre;
    private Queue<Integer> post;
    private Stack<Integer> reversePost;
    public DepthFIrstOrder(Diagraph G){
        pre=new Queue<>();
        post=new Queue<>();
        reversePost=new Stack<>();
        marked=new boolean[G.V()];
        for(int v=0;v<G.V();v++){
            if(!marked[v])
                dfs(G,v);
        }
    }
    private void dfs(Diagraph G,int v){
        pre.enqueue(v);//在递归调用前，加入队列
        marked[v]=true;
        for(int w:G.adj(v)){
            if(!marked[w]){
                dfs(G,w);
            }
        }
        post.enqueue(v);//在递归调用后加入队列
        reversePost.push(v);
    }
    public Iterable<Integer> pre(){
        return pre;
    }
    public Iterable<Integer> post(){
        return post;
    }
    public Iterable<Integer> reversePost(){
        return reversePost;
    }
}

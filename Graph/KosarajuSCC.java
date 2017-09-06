package Graph;

/**
 * Created by sunkai on 2017/9/5
 */
public class KosarajuSCC {
    //搜索图中的强连通分量
    private boolean[] marked;
    private int[] id;
    private int count;

    public KosarajuSCC(Diagraph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        DepthFIrstOrder order = new DepthFIrstOrder(G.reverse());
        for (int s : order.reversePost()) {
            if (!marked[s]) {
                dfs(G, s);
                count++;
            }
        }
    }

    private void dfs(Diagraph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                dfs(G, w);
            }
        }
    }

    public boolean stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    public int id(int v) {
        return id[v];
    }

    public int count() {
        return count;
    }
}

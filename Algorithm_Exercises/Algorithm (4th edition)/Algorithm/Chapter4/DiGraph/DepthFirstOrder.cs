using Chapter1;
using System;
using System.Text;

namespace Chapter4.DiGraph
{
    public class DepthFirstOrder
    {
        private bool[] marked;
        public Queue<int> Pre { get; } //顶点的前序
        public Queue<int> Post { get; } //顶点的后序
        public Stack<int> ReversePost { get; } //顶点的逆后续

        public DepthFirstOrder(IDiGraph G)
        {
            Pre = new Queue<int>();
            Post = new Queue<int>();
            ReversePost = new Stack<int>();
            marked = new bool[G.V];
            for (int v = 0; v < G.V; v++)
            {
                if (!marked[v])
                    Dfs(G, v);
            }
        }

        private void Dfs(IDiGraph g, int v)
        {
            Pre.Enqueue(v);
            marked[v] = true;
            foreach (int w in g.Adj(v))
            {
                if (!marked[w])
                    Dfs(g, w);
            }
            Post.Enqueue(v);
            ReversePost.Push(v);
        }
    }
}

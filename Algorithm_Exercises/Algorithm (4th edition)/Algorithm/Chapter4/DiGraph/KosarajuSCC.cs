using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public class KosarajuSCC : ISCC
    {
        public IDiGraph G { get; }

        private readonly bool[] marked;
        private readonly int[] id; //强连通分量标识符
        public int Count { get; private set; }

        public KosarajuSCC(IDiGraph G)
        {
            this.G = G;
            marked = new bool[G.V];
            id = new int[G.V];
            DepthFirstOrder order = new DepthFirstOrder(G.Reverse());
            foreach(int s in order.ReversePost)
                if(!marked[s])
                {
                    Dfs(G, s);
                    Count++;
                }
        }

        private void Dfs(IDiGraph g, int s)
        {
            marked[s] = true;
            id[s] = Count;
            foreach (int w in G.Adj(s))
            {
                if (!marked[w])
                    Dfs(g, w);
            }
        }

        public int Id(int v) => id[v];

        public bool StronglyConnected(int v, int w) => id[v] == id[w];
    }
}

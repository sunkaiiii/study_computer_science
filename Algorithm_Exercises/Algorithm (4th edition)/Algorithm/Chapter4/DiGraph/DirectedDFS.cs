using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public class DirectedDFS
    {
        private bool[] marked;
        //在G中找到s可达的所有顶点
        public DirectedDFS(IDiGraph G, int s)
        {
            marked = new bool[G.V];
            Dfs(G, s);
        }

        //在G中找到从source中的所有顶点可达的所有顶点
        public DirectedDFS(IDiGraph G, IEnumerable<int> sources)
        {
            marked = new bool[G.V];
            foreach (int s in sources)
                if (!marked[s])
                    Dfs(G, s);
        }

        private void Dfs(IDiGraph g, int s)
        {
            marked[s] = true;
            foreach (int w in g.Adj(s))
                if (!marked[w])
                    Dfs(g, w);
        }

        public bool Marked(int v) => marked[v];

    }
}

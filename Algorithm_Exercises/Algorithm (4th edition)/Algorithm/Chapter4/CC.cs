using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public class CC:ICC
    {
        private bool[] marked;
        private int[] id;
        private int count;

        public bool HasCycle { get; private set; } = false;
        public CC(IGraph G)
        {
            marked = new bool[G.V()];
            id = new int[G.V()];
            for(int s=0;s<G.V();s++)
            {
                if(!marked[s])
                {
                    Dfs(G, s,s);
                    count++;
                }
            }
        }

        private void Dfs(IGraph g, int v,int u)
        {
            marked[v] = true;
            id[v] = count;
            foreach (int w in g.Adj(v))
                if (!marked[w])
                    Dfs(g, w, v);
                else if (w != u)
                    HasCycle = true;
        }

        public bool Connected(int v, int w)
        {
            return id[v] == id[w];
        }

        public int CountCC()
        {
            return count;
        }

        public int Id(int v)
        {
            return id[v];
        }
    }
}

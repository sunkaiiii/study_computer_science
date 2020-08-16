using Chapter1;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public class Graph : IGraph
    {
        private int _v;
        private int _e;
        private Bag<int>[] adj;
        public Graph(int V)
        {
            Init(V);
        }

        private void Init(int V)
        {
            this._v = V;
            this._e = 0;
            adj = new Bag<int>[V];
            for (int v = 0; v < V; v++)
                adj[v] = new Bag<int>();
        }

        public Graph(Scanner scanner) 
        { 
            Init(scanner.ReadInt());
            int e = scanner.ReadInt();
            for(int i=0;i<e;i++)
            {
                int v = scanner.ReadInt();
                int w = scanner.ReadInt();
                AddEdge(v, w);
            }
        }

        public void AddEdge(int v, int w)
        {
            adj[v].Add(w);
            adj[w].Add(v);
            _e++;
        }
        public IEnumerable<int> Adj(int v) => adj[v];
        public int E() => _e;
        public  int V() => _v;

        //图的邻接表示法的字符串表示
        public override string ToString()
        {
            string s = V() + " vertices, " + E() + " edges\n";
            for(int v=0;v<V();v++)
            {
                s += v + ": ";
                foreach (int w in this.Adj(v))
                    s += w + " ";
                s += "\n";
            }
            return s;
        }
    }
}

using Chapter1;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public class DiGraph : IDiGraph
    {
        public int V { get; private set; }
        public int E { get; private set; }
        private Bag<int>[] adj;

        public DiGraph(int V)
        {
            Init(V);
        }

        public DiGraph(Scanner scanner)
        {
            Init(scanner.ReadInt());
            int e = scanner.ReadInt();
            for (int i = 0; i < e; i++)
            {
                int v = scanner.ReadInt();
                int w = scanner.ReadInt();
                AddEdge(v, w);
            }
        }
        private void Init(int V)
        {
            this.V = V;
            this.E = 0;
            adj = new Bag<int>[V];
            for (int v = 0; v < V; v++)
                adj[v] = new Bag<int>();
        }

        public void AddEdge(int v, int w)
        {
            adj[v].Add(w);
            E++;
        }

        public IEnumerable<int> Adj(int v)
        {
            return adj[v];
        }

        public IDiGraph Reverse()
        {
            IDiGraph R = new DiGraph(V);
            for (int v = 0; v < V; v++)
                foreach (int w in Adj(v))
                    R.AddEdge(w, v);
            return R;
        }

        public override string ToString()
        {
            string s = V + " vertices, " + E + " edges\n";
            for (int v = 0; v < V; v++)
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

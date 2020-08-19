using Chapter1;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public class EdgeWeightGraph:IEdgeWeightGraph
    {
        public int V { get; private set; }

        public int E { get; private set; }

        private Bag<IEdge>[] adj;

        public EdgeWeightGraph(int v)
        {
            Init(v);
        }

        public EdgeWeightGraph(Scanner scanner)
        {
            int v = scanner.ReadInt();
            Init(v);
            int e = scanner.ReadInt();
            for (int i = 0; i < e; i++)
            {
                int w = scanner.ReadInt();
                int g = scanner.ReadInt();
                double weight = scanner.ReadDouble();
                IEdge edge = new Edge(w, g, weight);
                AddEdge(edge);
            }
        }

        private void Init(int v)
        {
            this.V = v;
            this.E = 0;
            adj = new Bag<IEdge>[V];
            for (int i = 0; i < V; i++)
            {
                adj[i] = new Bag<IEdge>();
            }
        }

        public void AddEdge(IEdge e)
        {
            int v = e.Either;
            int w = e.Other(v);
            //两个点用的一个边
            adj[v].Add(e);
            adj[w].Add(e);
            E++;
        }

        public IEnumerable<IEdge> Adj(int v) => adj[v];

        public IEnumerable<IEdge> Edges()
        {
            Bag<IEdge> b = new Bag<IEdge>();
            for (int v = 0; v < V; v++)
            {
                foreach (IEdge edge in Adj(v))
                {
                    if (edge.Other(v) > v)
                        b.Add(edge);
                }
            }
            return b;
        }

        public override string ToString()
        {
            string s = V + " vertices, " + E + " edges\n";
            for (int v = 0; v < V; v++)
            {
                s += v + ": ";
                foreach (IEdge w in this.Adj(v))
                {
                    s += v + "-"+ w.Other(v)+" weight: "+ w.Weight+", ";
                }
                s += "\n";
            }
            return s;
        }
    }
}

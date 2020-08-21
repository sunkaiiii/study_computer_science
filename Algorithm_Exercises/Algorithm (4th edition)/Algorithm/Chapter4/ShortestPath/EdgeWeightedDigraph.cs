using Chapter1;
using Chapter4.DiGraph;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public class EdgeWeightedDigraph : IEdgeWeightedDIgraph
    {
        public int V { get; private set; }

        public int E { get; private set; }

        private Bag<IDirectedEdge>[] adj;

        public EdgeWeightedDigraph(int v)
        {
            Init(v);
        }

        public EdgeWeightedDigraph(Scanner scanner)
        {
            int v = scanner.ReadInt();
            Init(v);
            int e = scanner.ReadInt();
            for (int i = 0; i < e; i++)
            {
                int from = scanner.ReadInt();
                int to = scanner.ReadInt();
                double weight = scanner.ReadDouble();
                IDirectedEdge edge = new DirectedEdge(from, to, weight);
                AddEdge(edge);
            }
        }

        private void Init(int v)
        {
            this.V = v;
            this.E = 0;
            adj = new Bag<IDirectedEdge>[V];
            for (int i = 0; i < V; i++)
            {
                adj[i] = new Bag<IDirectedEdge>();
            }
        }

        public void AddEdge(IDirectedEdge e)
        {
            adj[e.From].Add(e);
            E++;
        }

        public IEnumerable<IDirectedEdge> Adj(int v) => adj[v];

        public IEnumerable<IDirectedEdge> Edges()
        {
            Bag<IDirectedEdge> bag = new Bag<IDirectedEdge>();
            for (int v = 0; v < V; v++)
            {
                foreach (var e in adj[v])
                {
                    bag.Add(e);
                }
            }
            return bag;
        }
    }
}

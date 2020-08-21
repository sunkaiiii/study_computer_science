using Chapter4.ShortestPath;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public class Topological
    {
        public IEnumerable<int> Order { get; } //顶点的拓扑顺序

        public Topological(IDiGraph G)
        {
            Order = Init(G);
        }

        private Chapter1.Stack<int> Init(IDiGraph G)
        {
            DirectedCycle cyclefinder = new DirectedCycle(G);
            if (!cyclefinder.HasCycle())
            {
                DepthFirstOrder dfs = new DepthFirstOrder(G);
                return dfs.ReversePost;
            }
            return null;
        }

        public Topological(IEdgeWeightedDIgraph G)
        {
            IDiGraph g = new DiGraph(G.V);
            for (int i = 0; i < G.V; i++)
            {
                foreach(var e in G.Adj(i))
                {
                    g.AddEdge(e.From, e.To);
                }
            }
            Order = Init(g);
        }

        public bool IsDag() => Order != null;
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public interface IEdgeWeightGraph
    {
        int V { get; }
        int E { get; }
        void AddEdge(IEdge e);
        IEnumerable<IEdge> Adj(int v);
        IEnumerable<IEdge> Edges();
        string ToString();
    }
}

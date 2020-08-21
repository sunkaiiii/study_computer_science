using Chapter4.DiGraph;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public interface IEdgeWeightedDIgraph
    {
        int V { get;}
        int E { get; }
        void AddEdge(IDirectedEdge e);
        IEnumerable<IDirectedEdge> Edges();
        IEnumerable<IDirectedEdge> Adj(int v);
    }
}

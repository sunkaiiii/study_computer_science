using System;
using System.Collections.Generic;

namespace Chapter4.ShortestPath
{
    public class EdgeWeightedCycleFinder
    {
        private bool[] marked;
        private IDirectedEdge[] edgeTo;
        private Stack<IDirectedEdge> cycle;
        private bool[] onStack;
        public EdgeWeightedCycleFinder(IEdgeWeightedDIgraph G)
        {
            onStack = new bool[G.V];
            edgeTo = new DirectedEdge[G.V];
            marked = new bool[G.V];
            for (int v = 0; v < G.V; v++)
            {
                if (!marked[v])
                    Dfs(G, v);
            }
        }

        private void Dfs(IEdgeWeightedDIgraph g, int v)
        {
            onStack[v] = true;
            marked[v] = true;
            foreach (var e in g.Adj(v))
            {
                int w = e.To;
                if (HasCycle())
                    return;
                else if(!marked[w])
                {
                    edgeTo[w] = e;
                    Dfs(g, w);
                }    else if (onStack[w])
                {
                    cycle = new Stack<IDirectedEdge>();
                    var x = e;
                    for(;x.From!=w;x=edgeTo[x.From])
                    {
                        cycle.Push(x);
                    }
                    cycle.Push(x);
                }
            }
            onStack[v] = false;
        }

        private bool HasCycle() => cycle != null;

        internal IEnumerable<IDirectedEdge> Cycle() => cycle;
    }
}
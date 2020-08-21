using Chapter4.DiGraph;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    //无环加权有向图最短路径算法
    public class AcyclicSP:AbsShortestPath
    {
        public AcyclicSP(IEdgeWeightedDIgraph G,int s):base(G,s)
        {
            Topological top = new Topological(G);
            foreach (int v in top.Order)
            {
                Relax(G, v);
            }
        }

        private void Relax(IEdgeWeightedDIgraph g, int v)
        {
            foreach (var e in g.Adj(v))
            {
                int w = e.To;
                if (distTo[w] > distTo[v] + e.Weight)
                {
                    distTo[w] = distTo[v] + e.Weight;
                    edgeTo[w] = e;
                }
            }
        }
    }
}

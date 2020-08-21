using Chapter2;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public class DijkstraSP:AbsShortestPath
    {
        private IndexMinPQ<double> pq;

        public DijkstraSP(IEdgeWeightedDIgraph G, int s):base(G,s)
        {
            pq = new IndexMinPQ<double>(G.V);
            pq.Insert(s, 0.0);
            while (!pq.IsEmpty)
                Relax(G, pq.DeleteMin());
        }

        private void Relax(IEdgeWeightedDIgraph g, int v)
        {
            foreach(var e in g.Adj(v))
            {
                int w = e.To;
                if(distTo[w]>distTo[v]+e.Weight)
                {
                    distTo[w] = distTo[v] + e.Weight;
                    edgeTo[w] = e;
                    if (pq.Contains(w))
                        pq.ChangeKey(w, distTo[w]);
                    else
                        pq.Insert(w, distTo[w]);
                }
            }
        }
    }
}

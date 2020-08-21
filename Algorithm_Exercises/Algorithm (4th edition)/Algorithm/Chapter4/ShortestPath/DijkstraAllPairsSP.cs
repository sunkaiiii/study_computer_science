using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public class DijkstraAllPairsSP
    {
        private DijkstraSP[] all;
        public DijkstraAllPairsSP(IEdgeWeightedDIgraph G)
        {
            all = new DijkstraSP[G.V];
            for (int v = 0; v < G.V; v++)
            {
                all[v] = new DijkstraSP(G, v);
            }
        }

        public IEnumerable<IDirectedEdge> Path(int s, int t)
        {
            return all[s].PathTo(t);
        }

        public double Dist(int s, int t)
        {
            return all[s].DistTo(t);
        }
    }
}

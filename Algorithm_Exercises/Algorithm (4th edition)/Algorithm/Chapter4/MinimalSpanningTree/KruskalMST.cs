using Chapter1;
using Chapter2;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public class KruskalMST : IMST
    {
        private readonly Chapter1.Queue<IEdge> mst;

        public KruskalMST(IEdgeWeightGraph G)
        {
            mst = new Chapter1.Queue<IEdge>();
            MinPQ<IEdge> pq = new MinPQ<IEdge>();
            foreach (var e in G.Edges())
            {
                pq.Insert(e);
            }
            UF uf = new UF(G.V);
            while(!pq.IsEmpty&&mst.Size<G.V-1)
            {
                IEdge e = pq.Delete(); //找到权重最小的边
                int v = e.Either, w = e.Other(v);
                if (uf.Connected(v, w)) //忽略失效的边
                    continue;
                uf.Union(v, w);
                mst.Enqueue(e);
            }
        }

        public double Weight { get
            {
                double w = 0.0;
                foreach (var e in Edges())
                {
                    w += e.Weight;
                }
                return w;
            } }

        public IEnumerable<IEdge> Edges() => mst;
    }
}

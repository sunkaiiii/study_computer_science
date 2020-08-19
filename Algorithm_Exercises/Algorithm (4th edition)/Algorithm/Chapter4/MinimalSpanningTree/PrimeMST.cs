using Chapter1;
using Chapter2;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public class PrimeMST:IMST
    {
        private IEdge[] edgeTo; //距离树最近的边
        private double[] distTo; //distTo[w]=edgeTo[w].weight()
        private bool[] marked;  //如果v在树中 则为true
        private IndexMinPQ<double> pq;//有效的横切边

        public PrimeMST(IEdgeWeightGraph G)
        {
            edgeTo = new Edge[G.V];
            distTo = new double[G.V];
            marked = new bool[G.V];
            for (int v = 0; v < G.V; v++)
            {
                distTo[v] = Double.PositiveInfinity;
            }
            pq = new IndexMinPQ<double>(G.V);
            distTo[0] = 0.0;
            pq.Insert(0, 0.0); //顶点0权重初始化
            while (!pq.IsEmpty)
                Visit(G, pq.DeleteMin());
        }

        public double Weight { get
            {
                double w = 0.0;
                foreach (var e in Edges())
                    w += e.Weight;
                return w;
            } }

        public IEnumerable<IEdge> Edges()
        {
            var mst = new Chapter1.Queue<IEdge>();
            for (int v = 0; v < edgeTo.Length; v++)
            {
                IEdge e = edgeTo[v];
                if (e != null)
                    mst.Enqueue(e);
            }
            return mst;
        }

        private void Visit(IEdgeWeightGraph g, int v)
        {
            marked[v] = true;
            foreach (var e in g.Adj(v))
            {
                int w = e.Other(v);
                if (marked[w])
                    continue;
                if(e.Weight<distTo[w]) //更新最佳的边
                {
                    edgeTo[w] = e;
                    distTo[w] = e.Weight;
                    if (pq.Contains(w))
                        pq.ChangeKey(w, distTo[w]);
                    else
                        pq.Insert(w, distTo[w]);
                }
            }
        }
    }
}



using Chapter1;
using Chapter2;
using System;
using System.Collections.Generic;

namespace Chapter4.MinimalSpanningTree
{
    public class LazyPrimMST:IMST
    {
        private bool[] marked;
        private Chapter1.Queue<IEdge> mst;
        private MinPQ<IEdge> pq;

        public LazyPrimMST(IEdgeWeightGraph g)
        {
            pq = new MinPQ<IEdge>();
            marked = new bool[g.V];
            mst = new Chapter1.Queue<IEdge>();
            Visit(g, 0);//假设G是联通的
            while(!pq.IsEmpty)
            {
                IEdge e = pq.Delete(); //找到权重最小的边
                int v = e.Either;
                int w = e.Other(v);
                if (marked[v] && marked[w]) //跳过失效的边
                    continue;
                mst.Enqueue(e); //将边添加到树中
                if (!marked[v])
                    Visit(g, v);
                if (!marked[w])
                    Visit(g, w);
            }
        }

        private void Visit(IEdgeWeightGraph g, int v)
        {
            //标记顶点v并将所有链接v和未被标记的顶点加入pq
            marked[v] = true;
            foreach (var edge in g.Adj(v))
            {
                if (!marked[edge.Other(v)])
                    pq.Insert(edge);
            }
        }

        public double Weight { get
            {
                double w = 0.0;
                foreach(var e in Edges())
                {
                    if (e != null)
                        w += e.Weight;
                }
                return w;
            } }

        public IEnumerable<IEdge> Edges() => mst;
    }
}

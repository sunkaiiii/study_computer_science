using Chapter1;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public class BellmanFordSP:AbsShortestPath
    {
        private bool[] onQ; //该顶点是否在队列中
        private Chapter1.Queue<int> queue; //正在被放松的点
        private int cost; //relax的调用次数
        private IEnumerable<IDirectedEdge> cycle; //edgeTo中是否含有负权重环

        public BellmanFordSP(IEdgeWeightedDIgraph G,int s):base(G,s)
        {
            onQ = new bool[G.V];
            queue = new Chapter1.Queue<int>();
            queue.Enqueue(s);
            onQ[s] = true;
            while(!queue.IsEmpty&&!HasNegativeCycle())
            {
                int v = queue.Dequeue();
                onQ[v] = false;
                Relax(G,v);
            }
        }

        private bool HasNegativeCycle() => cycle != null;

        private void Relax(IEdgeWeightedDIgraph g, int v)
        {
            foreach (var e in g.Adj(v))
            {
                int w = e.To;
                if (distTo[w] > distTo[v] + e.Weight)
                {
                    distTo[w] = distTo[v] + e.Weight;
                    edgeTo[w] = e;
                    if (!onQ[w])
                    {
                        queue.Enqueue(w);
                        onQ[w] = true;
                    }
                }
                if (cost++ % g.V == 0)
                    FindNegativeCycle();
            }
        }

        private void FindNegativeCycle()
        {
            int v = edgeTo.Length;
            IEdgeWeightedDIgraph spt = new EdgeWeightedDigraph(v);
            for (int i = 0; i < v; i++)
            {
                if (edgeTo[i] != null)
                    spt.AddEdge(edgeTo[i]);
            }
            EdgeWeightedCycleFinder cf = new EdgeWeightedCycleFinder(spt);
            cycle = cf.Cycle();
        }
    }
}

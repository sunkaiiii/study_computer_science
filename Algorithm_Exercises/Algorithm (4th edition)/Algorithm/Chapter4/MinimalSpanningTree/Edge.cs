using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public class Edge : IEdge
    {
        private int V { get; }
        private int W { get; }
        public double Weight { get; }

        public Edge(int v, int w, double weight)
        {
            this.V = v;
            this.W = w;
            this.Weight = weight;
        }


        //当两个顶点都是未知的时候，可以使用v=e.either(),w=e.other(v) 来得到两个顶点
        public int Either => V; 

        public int CompareTo([AllowNull] IEdge that)
        {
            if (this.Weight < that.Weight)
                return -1;
            else if (this.Weight > that.Weight)
                return 1;
            else
                return 0;
        }

        public int Other(int v) //一直一个顶点V，可以得到边的另外一个顶点
        {
            if (v == V)
                return W;
            else if (v == W)
                return V;
            else
                throw new Exception("Inconssitent edge");
        }

        public override string ToString()
        {
            return V + " " + W + "weight: " + Weight;
        }
    }
}

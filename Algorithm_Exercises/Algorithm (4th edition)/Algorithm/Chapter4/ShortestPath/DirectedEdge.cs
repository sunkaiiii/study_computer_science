using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public class DirectedEdge : IDirectedEdge
    {
        private int V {  get; }
        private int W { get; }
        public double Weight { get; }

        public DirectedEdge(int v,int w, double weight)
        {
            this.V = v;
            this.W = w;
            this.Weight = weight;
        }

        public int From => V;

        public int To => W;

        public override string ToString()
        {
            return string.Format("{0}->{1} {2}", V, W, Weight);
        }
    }
}

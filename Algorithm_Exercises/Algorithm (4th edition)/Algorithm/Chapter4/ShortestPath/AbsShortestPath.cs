using Chapter1;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public abstract class AbsShortestPath : IShortestPath
    {
        protected double[] distTo;
        protected IDirectedEdge[] edgeTo;

        public AbsShortestPath(IEdgeWeightedDIgraph G, int s)
        {
            edgeTo = new DirectedEdge[G.V];
            distTo = new double[G.V];
            for (int v = 0; v < G.V; v++)
            {
                distTo[v] = Double.PositiveInfinity;
            }
            distTo[s] = 0.0;
        }


        protected void Relax(IDirectedEdge e)
        {
            int v = e.From, w = e.To;
            if(DistTo(w)>DistTo(v)+e.Weight)
            {
                distTo[w] = distTo[v] + e.Weight;
                edgeTo[w] = e;
            }
        }
        public double DistTo(int v) => distTo[v];
        public bool HasPathTo(int v) => distTo[v] < Double.PositiveInfinity;
        public  IEnumerable<IDirectedEdge> PathTo(int v)
        {
            if (!HasPathTo(v))
                return null;
            Chapter1.Stack<IDirectedEdge> path = new Chapter1.Stack<IDirectedEdge>();
            for(var e = edgeTo[v];e!=null;e=edgeTo[e.From])
            {
                path.Push(e);
            }
            return path;
        }
    }
}

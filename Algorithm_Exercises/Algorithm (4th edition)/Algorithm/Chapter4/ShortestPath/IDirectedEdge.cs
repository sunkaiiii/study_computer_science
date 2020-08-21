using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public interface IDirectedEdge
    {
        double Weight { get; }
        int From { get; }
        int To { get; }
        string ToString();
    }
}

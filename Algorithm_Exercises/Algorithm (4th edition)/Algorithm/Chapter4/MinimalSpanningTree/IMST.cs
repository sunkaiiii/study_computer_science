using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public interface IMST
    {
        IEnumerable<IEdge> Edges();
        double Weight { get; }
    }
}

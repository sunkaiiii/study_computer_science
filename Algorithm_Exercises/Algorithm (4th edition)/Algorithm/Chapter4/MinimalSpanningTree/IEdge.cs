using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.MinimalSpanningTree
{
    public interface IEdge:IComparable<IEdge>
    {
        double Weight { get; }
        int Either { get; }
        int Other(int v);
        string ToString();
        
    }
}

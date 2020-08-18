using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public interface ISCC
    {
        IDiGraph G { get; }
        bool StronglyConnected(int v, int w);
        int Count { get; }
        int Id(int v);
    }
}

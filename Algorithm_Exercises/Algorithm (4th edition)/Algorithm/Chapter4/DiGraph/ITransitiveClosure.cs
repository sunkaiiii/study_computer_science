using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public interface ITransitiveClosure
    {
        bool Rechable(int v, int w);
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public interface IPath
    {
        public IGraph G { get; }
        public int S { get; }
        bool HasPathTo(int v);
        IEnumerable<int> PathTo(int v);
    }
}

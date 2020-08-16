using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public interface ISearch
    {
        public IGraph G { get; }
        public int S { get; }
        bool Marked(int v);
        int Count();
    }
}

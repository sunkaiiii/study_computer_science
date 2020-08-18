using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    class Topological
    {
        public IEnumerable<int> Order { get; } //顶点的拓扑顺序

        public Topological(IDiGraph G)
        {
            DirectedCycle cyclefinder = new DirectedCycle(G);
            if(!cyclefinder.HasCycle())
            {
                DepthFirstOrder dfs = new DepthFirstOrder(G);
                Order = dfs.ReversePost;
            }
        }

        public bool IsDag() => Order != null;
    }
}

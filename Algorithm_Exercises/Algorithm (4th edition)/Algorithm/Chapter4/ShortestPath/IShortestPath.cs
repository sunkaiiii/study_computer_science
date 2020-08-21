using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.ShortestPath
{
    public interface IShortestPath
    {
        double DistTo(int v); //从顶点s到v的距离，如果不存在路径则为无穷大
        bool HasPathTo(int v);
        IEnumerable<IDirectedEdge> PathTo(int v);
    }
}

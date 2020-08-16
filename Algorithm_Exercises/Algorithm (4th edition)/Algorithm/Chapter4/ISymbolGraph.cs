using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public interface ISymbolGraph
    {
        bool Contains(string key); //key是否是顶点
        int Index(string key);//key的索引
        string Name(int v);//索引v的顶点名
        IGraph G { get; }
    }
}

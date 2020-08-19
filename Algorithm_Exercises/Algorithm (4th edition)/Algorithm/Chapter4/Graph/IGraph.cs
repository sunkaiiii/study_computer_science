using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public interface IGraph
    {
        int V { get; }//顶点数
        int E { get; }//边数
        void AddEdge(int v, int w);
        IEnumerable<int> Adj(int v); //和v相邻的所有顶点
        string ToString();
    }
}

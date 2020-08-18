using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public interface IDiGraph
    {
        int V { get; }
        int E { get; }
        void AddEdge(int v, int w); //向有向图中添加一条边v->w
        IEnumerable<int> Adj(int v); //由v指出的边所连接的所有顶点
        IDiGraph Reverse();//该图的反向图
        string ToString();
    }
}

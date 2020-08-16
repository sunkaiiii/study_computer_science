using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    //连通分量
    public interface ICC
    {
        bool Connected(int v, int w); //v和w是否连通
        int CountCC(); //连通分量数
        int Id(int v);//v所在的连通分量标识符
        bool HasCycle { get; }
    }
}

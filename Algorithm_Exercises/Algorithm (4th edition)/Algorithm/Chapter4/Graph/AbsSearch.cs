using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public abstract class AbsSearch:ISearch,IPath
    {
        public IGraph G { get; }

        public int S { get; }

        public AbsSearch(IGraph g,int s)
        {
            this.G = g;
            this.S = s;
        }

        //v和s是否连通
        public abstract bool Marked(int v);

        //与s连通的定点总数
       public abstract  int Count();
        public abstract bool HasPathTo(int v);
        public abstract IEnumerable<int> PathTo(int v);
    }
}

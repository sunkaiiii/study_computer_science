using Chapter1;
using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace Chapter4
{
    class BreadthFirstPaths : AbsSearch
    {
        private bool[] marked;
        private int[] edgeTo;
        
        public BreadthFirstPaths(IGraph g,int s):base(g,s)
        {
            marked = new bool[g.V()];
            edgeTo = new int[g.V()];
            Bfs(g, s);
        }

        private void Bfs(IGraph g, int s)
        {
            var queue = new Chapter1.Queue<int>();
            marked[s] = true; //起点被标记
            queue.Enqueue(s);
            while(!queue.IsEmpty)
            {
                int v= queue.Dequeue(); //从队列中删除一个顶点
                foreach(int w in g.Adj(v))
                    if(!marked[w])
                    {
                        edgeTo[w] = v;
                        marked[w] = true;
                        queue.Enqueue(w); 
                    }
            }
        }

        public override int Count()
        {
            throw new NotImplementedException();
        }

        public override bool HasPathTo(int v)
        {
            return marked[v];
        }

        public override bool Marked(int v)
        {
            return marked[v];
        }

        public override IEnumerable<int> PathTo(int v)
        {
            if (!HasPathTo(v))
                return null;
            Chapter1.Stack<int> path = new Chapter1.Stack<int>();
            for (int x = v; x != S; x = edgeTo[x])
                path.Push(x);
            path.Push(S);
            return path;
        }
    }
}

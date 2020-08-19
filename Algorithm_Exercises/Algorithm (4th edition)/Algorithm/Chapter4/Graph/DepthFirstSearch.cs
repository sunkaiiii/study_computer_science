using Chapter1;
using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace Chapter4
{
    public class DepthFirstSearch:AbsSearch
    {
        private bool[] marked;
        private int CountNum { get; set; } = 0;
        private int[] edgeTo;
        private ICC cc;
        public DepthFirstSearch(IGraph graph,int s) : base(graph, s)
        {
            marked = new bool[graph.V];
            edgeTo = new int[graph.V];
            Dfs(graph, s);
        }

        private void Dfs(IGraph graph, int v)
        {
            marked[v] = true;
            CountNum++;
            foreach (int w in graph.Adj(v))
                if (!marked[w]) //如果没有走过，则继续深度遍历
                {
                    edgeTo[w] = v;
                    Dfs(graph, w);
                }

        }

        public override bool Marked(int v)
        {
            return marked[v];
        }

        public override int Count()
        {
            return CountNum;
        }

        public override bool HasPathTo(int v)
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

        public ICC InitCC()
        {
            if (cc == null)
                cc = new CC(G);
            return cc;
        }
    }
}

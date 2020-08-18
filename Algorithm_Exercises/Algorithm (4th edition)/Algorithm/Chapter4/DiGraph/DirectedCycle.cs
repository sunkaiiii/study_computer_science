using Chapter1;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4.DiGraph
{
    public class DirectedCycle
    {
        private bool[] marked;
        private int[] edgeTo;
        private Chapter1.Stack<int> cycle; //有向环中的顶点
        private bool[] onStack; //递归调用的栈上的所有顶点

        public DirectedCycle(IDiGraph G)
        {
            onStack = new bool[G.V];
            edgeTo = new int[G.V];
            marked = new bool[G.V];
            for (int v = 0; v < G.V; v++)
            {
                if (!marked[v])
                    Dfs(G, v);
            }
        }

        private void Dfs(IDiGraph g, int v)
        {
            onStack[v] = true;
            marked[v] = true;
            foreach (int w in g.Adj(v))
            {
                if (HasCycle())
                    return;
                else if (!marked[w])
                {
                    edgeTo[w] = v;
                    Dfs(g, w);
                }else if(onStack[w])
                {
                    cycle = new Chapter1.Stack<int>();
                    for(int x=v;x!=w;x=edgeTo[x])
                    {
                        cycle.Push(x);
                    }
                    cycle.Push(w);
                    cycle.Push(v);
                }
                onStack[v] = false;
            }
        }

        public bool HasCycle() => cycle != null;

        public IEnumerable<int> Cycle() => cycle;
    }
}

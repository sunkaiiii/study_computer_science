using System;
using Chapter1;
using Chapter4.DiGraph;

namespace Chapter5.Regax
{
    public class NFARegex
    {
        IDiGraph G { get; set; }
        int M { get; set; }
        char[] Re { get; set; }
        public NFARegex(string regexp)
        {
            Stack<int> ops = new Stack<int>();
            Re = regexp.ToCharArray();
            M = Re.Length;
            G = new DiGraph(M + 1);
            for (int i = 0; i < M; i++)
            {
                int lp = i;
                if(Re[i]=='('||Re[i]=='|')
                {
                    ops.Push(i);
                }else if(Re[i]==')')
                {
                    int or = ops.Pop();
                    if(Re[or]=='|')
                    {
                        lp = ops.Pop();
                        G.AddEdge(lp, or + 1);
                        G.AddEdge(or, i);
                    }
                    else
                    {
                        lp = or;
                    }
                }
                if(i<M-1&&Re[i+1]=='*') //查看下一个字符
                {
                    G.AddEdge(lp, i + 1);
                    G.AddEdge(i + 1, lp);
                }
                if(Re[i]=='('||Re[i]=='*'||Re[i]==')')
                {
                    G.AddEdge(i, i + 1);
                }
            }
        }

        public bool Recognizes(string txt)
        {
            Bag<int> pc = new Bag<int>();
            DirectedDFS dfs = new DirectedDFS(G, 0);
            for (int v = 0; v < G.V; v++)
            {
                if (dfs.Marked(v))
                {
                    pc.Add(v);
                }
            }
            for (int i = 0; i < txt.Length; i++)
            {
                //计算txt[i+1]可能到达的所有MFA状态
                var match = new Bag<int>();
                foreach(int v in pc)
                {
                    if(v<M)
                    {
                        if(Re[v]==txt[i]||Re[v]=='.')
                        {
                            match.Add(v + 1);
                        }
                    }
                }
                pc = new Bag<int>();
                dfs = new DirectedDFS(G, match);
                for (int v = 0; v < G.V; v++)
                {
                    if(dfs.Marked(v))
                    {
                        pc.Add(v);
                    }
                }
            }
            foreach(int v in pc)
            {
                if(v==M)
                {
                    return true;
                }

            }
            return false;
        }
    }
}

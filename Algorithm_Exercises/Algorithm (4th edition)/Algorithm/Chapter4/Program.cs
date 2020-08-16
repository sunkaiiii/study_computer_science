using Chapter1;
using Chapter3;
using StandardLibraries;
using System;
using System.IO;

namespace Chapter4
{
    class Program
    {
        static void Main(string[] args)
        {
            Graph graph = new Graph(new Scanner(new StreamReader(File.OpenRead("tinyG.txt"))));
            Graph graph2 = new Graph(new Scanner(new StreamReader(File.OpenRead("tinyCG.txt"))));
            StdOut.Println("输入一个数字: ");
            int s = StdIn.ReadInt();
            ISearch search = new DepthFirstSearch(graph, s);
            for (int v = 0; v < graph.V(); v++)
                if (search.Marked(v))
                    StdOut.Print(v + " ");
            StdOut.Println();
            StdOut.Println();
            StdOut.Println();

            ICC cc = new DepthFirstSearch(graph, s).InitCC();
            int M = cc.CountCC();
            StdOut.Println(M + " components");
            Bag<int>[] components = new Bag<int>[M];
            for (int i = 0; i < M; i++)
                components[i] = new Bag<int>();
            for (int v = 0; v < graph.V(); v++)
                components[cc.Id(v)].Add(v);
            for (int i = 0; i < M; i++)
            {
                foreach (int v in components[i])
                    StdOut.Print(v + " ");
                StdOut.Println();
            }
            StdOut.Println(cc.HasCycle);

            if (search.Count() != graph.V())
                StdOut.Print("Not ");
            StdOut.Println("connected");

            IPath path = new DepthFirstSearch(graph2, s);
            for (int v = 0; v < graph2.V(); v++)
            {
                StdOut.Print(s + " to " + v + ": ");
                if (path.HasPathTo(v))
                {
                    foreach (int x in path.PathTo(v))
                        if (x == s)
                            StdOut.Print(x);
                        else
                            StdOut.Print("-" + x);
                }
                StdOut.Println();
            }


            //符号图
            string filename = "routes.txt";
            string filename2 = "movies.txt";
            string delim = "/";
            ISymbolGraph sg = new SymbolGraph(filename2, delim);
            IGraph g = sg.G;
            while (StdIn.HasNextLine())
            {
                StdOut.Println("输入查找的字符串");
                string source = StdIn.ReadLine();
                foreach (int w in g.Adj(sg.Index(source)))
                    StdOut.Println("   " + sg.Name(w));
            }

        }
    }
}

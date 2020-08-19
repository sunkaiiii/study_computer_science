using Chapter1;
using Chapter3;
using Chapter4.DiGraph;
using Chapter4.MinimalSpanningTree;
using StandardLibraries;
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Chapter4
{
    class Program
    {
        private static void Graph()
        {
            Graph graph = new Graph(new Scanner(new StreamReader(File.OpenRead("tinyG.txt"))));
            Graph graph2 = new Graph(new Scanner(new StreamReader(File.OpenRead("tinyCG.txt"))));
            StdOut.Println("输入一个数字: ");
            int s = StdIn.ReadInt();
            ISearch search = new DepthFirstSearch(graph, s);
            for (int v = 0; v < graph.V; v++)
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
            for (int v = 0; v < graph.V; v++)
                components[cc.Id(v)].Add(v);
            for (int i = 0; i < M; i++)
            {
                foreach (int v in components[i])
                    StdOut.Print(v + " ");
                StdOut.Println();
            }
            StdOut.Println(cc.HasCycle);

            if (search.Count() != graph.V)
                StdOut.Print("Not ");
            StdOut.Println("connected");

            IPath path = new DepthFirstSearch(graph2, s);
            for (int v = 0; v < graph2.V; v++)
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

        private static void DiGraph()
        {
            IDiGraph G = new DiGraph.DiGraph(new Scanner(new StreamReader(File.OpenRead("tinyDG.txt"))));
            Bag<int> sources = new Bag<int>();
            StdOut.Println("搜索几个结点：");
            int i = StdIn.ReadInt();
            while (i-- > 0)
            {
                sources.Add(StdIn.ReadInt());
            }
            DirectedDFS reachable = new DirectedDFS(G, sources);
            for (int v = 0; v < G.V; v++)
                if (reachable.Marked(v))
                    StdOut.Print(v + " ");

            //string filename = "jobs.txt"; //文件有问题
            //string seperator = "/";
            //SymbolDiGraph sg = new SymbolDiGraph(filename, seperator);
            //Topological topological = new Topological(sg.G);
            //foreach (int v in topological.Order)
            //    StdOut.Println(sg.Name(v));

            StdOut.Println();
            StdOut.Println("强连通分量的数量");
            ISCC scc = new KosarajuSCC(G);
            StdOut.Println(scc.Count);
        }

        private static void MST()
        {
            int i = 0;
            StdOut.Println("输入选择：0，1");
            i = StdIn.ReadInt();
            string filename = i switch
            {
                0 => "tinyEWG.txt",
                1 => "mediumEWG.txt",
                _ => throw new Exception("no file name is assigned"),
            };
            IEdgeWeightGraph G = new EdgeWeightGraph(new Scanner(new StreamReader(File.OpenRead(filename))));
            IMST mst = new LazyPrimMST(G);
            IMST mst2 = new PrimeMST(G); 
            IMST mst3 = new KruskalMST(G);
            ShowMSTResult(G, mst);
            ShowMSTResult(G, mst2);
            ShowMSTResult(G, mst3);
        }

        private static void ShowMSTResult(IEdgeWeightGraph G, IMST mst)
        {
            //StdOut.Println(G.ToString());
            foreach (var edge in mst.Edges())
            {
                StdOut.Println(edge);
            }
            StdOut.Println(mst.Weight);
        }

        static void Main(string[] args)
        {
            //Graph();
            //DiGraph();
            MST();
        }


    }
}

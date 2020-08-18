using Chapter3;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Chapter4
{
    class SymbolGraph:ISymbolGraph
    {
        private ISearchTable<string, int?> st; //符号名->索引
        private readonly string[] keys; //索引->符号名
        public IGraph G { get; } //图
        public SymbolGraph(string filename,string delim,SearchTableOptions options=SearchTableOptions.RedBlack)
        {
            st = SearchTableExamples.CreateSearchTable<string, int?>(options);
            Scanner scanner = new Scanner(new StreamReader(File.OpenRead(filename)));
            while(scanner.HasNextLine()) //构造索引
            {
                string[] a = scanner.ReadLine().Split(delim); //为每个不同的字符串关联一个索引
                for(int i=0;i<a.Length;i++)
                {
                    if (!st.Contains(a[i]))
                        st.Put(a[i], st.Size);
                }
            }
            keys = new string[st.Size]; //用来获得顶点名反向索引
            
            foreach(string name in st.Keys())
            {
                keys[st.Get(name)??-1] = name;
            }
            G = new Graph(st.Size);
            scanner = new Scanner(new StreamReader(File.OpenRead(filename))); //第二遍
            while(scanner.HasNextLine())
            {
                string[] a = scanner.ReadLine().Split(delim); //将每一行的第一个顶点和该行的其他顶点相连
                int v = st.Get(a[0])??-1;
                for (int i = 1; i < a.Length; i++)
                    G.AddEdge(v, st.Get(a[i])??-1);
            }
        }

        public bool Contains(string key)
        {
            return st.Contains(key);
        }

        public int Index(string key)
        {
            return st.Get(key)??-1;
        }

        public string Name(int v)
        {
            return keys[v];
        }
    }
}

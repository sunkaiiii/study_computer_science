using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter4
{
    public static class GraphHelper
    {
        //计算V的度数
        public static int Degree(IGraph g, int v)
        {
            int degree = 0;
            foreach (int w in g.Adj(v))
                ++degree;
            return degree;
        }

        //计算所有顶点的最大度数
        public static int MaxDegree(IGraph G)
        {
            int max = 0;
            for (int v = 0; v < G.V; v++)
                if (Degree(G, v) > max)
                    max = Degree(G, v);
            return max;
        }

        //计算所有顶点的平均度数
        public static double AvgDegree(IGraph g)
        {
            return 2.0 * g.E / g.V;
        }

        //计算自环的个数
        public static int NumberOfSelfLoops(IGraph g)
        {
            int count = 0;
            for (int v = 0; v < g.V; v++)
                foreach (int w in g.Adj(v))
                    if (v == w)
                        count++;
            return count / 2; //每条边都被记过两次
        }

    }
}

using System;
using System.Collections.Generic;
using System.Reflection.Metadata.Ecma335;
using System.Text;

namespace Chapter4.DiGraph
{
    public class TransitiveClosure:ITransitiveClosure
    {
        private DirectedDFS[] all;
        public TransitiveClosure(IDiGraph G)
        {
            all = new DirectedDFS[G.V];
            for (int v = 0; v < G.V; v++)
            {
                all[v] = new DirectedDFS(G, v);
            }
        }

        public bool Rechable(int v, int w) => all[v].Marked(w);
    }
}

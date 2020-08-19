using System;
namespace Chapter1
{
    public class UF
    {
        private int[] id;
        private int Count { get; set; }
        public UF(int N)
        {
            Count = N;
            id = new int[N];
            for (int i = 0; i < N; i++)
                id[i] = i;
        }

        public bool Connected(int p, int q) => Find(p) == Find(q);

        public int Find(int p)
        {
            while (p != id[p])
                p = id[p];
            return p;
        }

        public void Union(int p, int q)
        {
            int pRoot = Find(p);
            int qRoot = Find(q);
            if (pRoot == qRoot)
                return;
            id[pRoot] = qRoot;
            Count--;
        }
                
    }
}

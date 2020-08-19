using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter2
{
    public class MinPQ<Key> : IPriorityQueue<Key> where Key : IComparable<Key>
    {
        private Key[] pq;

        public int Size { get; private set; } = 0;

        public bool IsEmpty => Size == 0;

        public Key Min => pq[1];

        public MinPQ(int initCapacity)
        {
            pq = new Key[initCapacity];
            Size = 0;
        }

        public MinPQ() : this(1) { }

        public MinPQ(Key[] keys)
        {
            Size = keys.Length;
            pq = new Key[keys.Length + 1];
            for (int i = 0; i < Size; i++)
            {
                pq[i + 1] = keys[i];
            }
            for (int k = Size / 2; k >= 1; k--)
                Sink(k);
        }

        private void Resize(int capacity)
        {
            Key[] temp = new Key[capacity];
            for (int i = 0; i <=Size; i++)
            {
                temp[i] = pq[i];
            }
            pq = temp;
        }

        private void Sink(int k)
        {
            while (2 * k <= Size)
            {
                int j = 2 * k;
                if (j < Size && Greater(j, j + 1)) j++;
                if (!Greater(k, j)) break;
                Exch(k, j);
                k = j;
            }
        }

        public Key Delete()
        {
            Key min = pq[1];
            Exch(1, Size--);
            Sink(1);
            pq[Size + 1] = default;
            if ((Size > 0) && (Size == (pq.Length - 1) / 4))
                Resize(pq.Length / 2);
            return min;
        }

        private void Exch(int i, int j)
        {
            Key swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
        }

        public void Insert(Key v)
        {
            if (Size== pq.Length - 1)
                Resize(2 * pq.Length);
            pq[++Size] = v;
            Swim(Size);
        }


        private void Swim(int k)
        {
            while (k > 1 && Greater(k / 2, k))
            {
                Exch(k, k / 2);
                k = k / 2;
            }
        }

        private bool Greater(int v, int k)
        {
            return pq[v].CompareTo(pq[k]) > 0;
        }

        public Key Top()
        {
            throw new NotImplementedException();
        }
    }
}

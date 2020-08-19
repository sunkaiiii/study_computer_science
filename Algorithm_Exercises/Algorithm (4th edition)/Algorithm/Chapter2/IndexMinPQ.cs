using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace Chapter2
{
    public class IndexMinPQ<Key> where Key : IComparable<Key>
    {
        private int MaxN { get; set; }
        private int[] pq;
        private int[] qp;
        private Key[] keys;

        public IndexMinPQ(int maxN)
        {
            this.MaxN = maxN;
            Size = 0;
            keys = new Key[maxN + 1];
            pq = new int[maxN + 1];
            qp = new int[maxN + 1];
            for (int i = 0; i <= maxN; i++)
            {
                qp[i] = -1;
            }
        }

        public bool IsEmpty => Size == 0;

        public int Size { get; private set; }

        public bool Contains(int i)
        {
            ValidateIndex(i);
            return qp[i] != -1;
        }

        private void ValidateIndex(int i)
        {
            if (i < 0) throw new Exception("index is negative: " + i);
            if (i >= MaxN) throw new Exception("index >= capacity: " + i);
        }

        public void Delete(int i)
        {
            ValidateIndex(i);
            int index = qp[i];
            Exchange(index, Size--);
            Swim(index);
            Sink(index);
            keys[i] = default;
            qp[i] = -1;
        }

        public int DeleteMin()
        {
            int min = pq[1];
            Exchange(1, Size--);
            Sink(1);
            qp[min] = -1;
            pq[Size + 1] = -1;
            keys[min] = default;
            return min;
        }

        public Key KeyOf(int i)
        {
            ValidateIndex(i);
            if (!Contains(i))
                throw new Exception("Index is not in the priority queue");
            return keys[i];
        }

        public void ChangeKey(int i, Key key)
        {
            ValidateIndex(i);
            if (!Contains(i))
                throw new Exception("Index is not in the priority queue");
            keys[i] = key;
            Swim(qp[i]);
            Sink(qp[i]);
        }

        private void Sink(int k)
        {
            while (2 * k <= Size)
            {
                int j = 2 * k;
                if (j < Size && Greater(j, j + 1)) j++;
                if (!Greater(k, j)) break;
                Exchange(k, j);
                k = j;
            }
        }

        private void Exchange(int i, int j)
        {
            int swap = pq[i];
            pq[i] = pq[j];
            pq[j] = swap;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }

        public void Insert(int i,Key key)
        {
            ValidateIndex(i);
            if (Contains(i))
                throw new Exception("Index is already in the priority queue");
            Size++;
            qp[i] = Size;
            pq[Size] = i;
            keys[i] = key;
            Swim(Size);
        }

        public void DecreaseKey(int i,Key key)
        {
            ValidateIndex(i);
            if (Contains(i))
                throw new Exception("Index is already in the priority queue");
            if (keys[i].CompareTo(key) == 0)
                throw new Exception("Calling decreaseKey() with a key equal to the key in the priority queue");
            if(keys[i].CompareTo(key)<0)
                throw new Exception("Calling decreaseKey() with a key strictly greater than the key in the priority queue");
            keys[i] = key;
            Swim(qp[i]);
        }

        public void IncreaseKey(int i, Key key)
        {
            ValidateIndex(i);
            if (Contains(i))
                throw new Exception("Index is already in the priority queue");
            if (keys[i].CompareTo(key) == 0)
                throw new Exception("Calling increaseKey() with a key equal to the key in the priority queue");
            if (keys[i].CompareTo(key) > 0)
                throw new Exception("Calling increaseKey() with a key strictly less than the key in the priority queue");
            keys[i] = key;
            Sink(qp[i]);
        }

        private void Swim(int k)
        {
            while (k > 1 && Greater(k / 2, k))
            {
                Exchange(k, k / 2);
                k = k / 2;
            }
        }

        public int MinIndex => pq[1];

        public Key MinKey => keys[pq[1]];

        public Key Top()
        {
            throw new NotImplementedException();
        }

        private bool Greater(int i, int j)
        {
            return keys[pq[i]].CompareTo(keys[pq[j]]) > 0;
        }


    }
}

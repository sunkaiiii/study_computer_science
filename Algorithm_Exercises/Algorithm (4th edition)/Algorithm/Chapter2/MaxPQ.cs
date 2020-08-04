using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter2
{
    //泛型优先队列
    public class MaxPQ<T> : IPriorityQueue<T> where T : IComparable<T>
    {

        T[] pq;

        public MaxPQ()
        {

        }

        public MaxPQ(int max)
        {
            pq = new T[max + 1];
        }

        public MaxPQ(T[] a)
        {
            pq = new T[a.Length+1];
            foreach(T item in a)
            {
                Insert(item);
            }
        }
        public bool IsEmpty { get => Size==0; }
        public int Size { get; private set; } = 0;

        private bool Less(int i,int j)
        {
            return pq[i].CompareTo(pq[j]) < 0;
        }

        private void Exchange(int i,int j)
        {
            T t = pq[i];
            pq[i] = pq[j];
            pq[j] = t;
        }

        //由下至上的上浮
        private void Swim(int k)
        {
            while(k>1 &&Less(k/2,k))
            {
                Exchange(k / 2, k);
                k /= 2;
            }
        }

        //由上至下的下沉
        private void Sink(int k)
        {
            Sink(k, Size);
        }

        private void Sink(int k, int size)
        {
            while (2 * k <= size)
            {
                int j = 2 * k;
                if (j < size && Less(j, j + 1))
                    j++;
                if (!Less(k, j))
                    break;
                Exchange(k, j);
                k = j;
            }
        }

        public T Delete()
        {
            T max = pq[1];
            Exchange(1, Size--); //和最后一个元素交换
            pq[Size + 1] = default(T);
            Sink(1); //下沉这个交换过的节点，恢复堆的有序性
            return max;
        }

        public void Insert(T v)
        {
            pq[++Size] = v;
            Swim(Size);
        }

        public T Top()
        {
            return pq[1];
        }

        public T[] Get() => pq;

        public void Sort()
        {
            int N = Size;
            for (int k = N / 2; k >= 1; k--)
                Sink(k,N);
            while(N>1)
            {
                Exchange(1, N--);
                Sink(1, N);
            }
        }
    }
}

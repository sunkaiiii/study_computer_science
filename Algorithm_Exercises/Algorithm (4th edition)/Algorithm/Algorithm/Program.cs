using Chapter1;
using StandardLibraries;
using System;
using System.Collections;
using System.Linq;

namespace Algorithm
{
    class Program
    {
        //最大公约数，欧几里得算法
        public static int Gcd(int p, int q)
        {
            if (q == 0)
                return p;
            int r = p % q;
            return Gcd(q, r);
        }

        //二分查找
        //数组必须是有序的
        public static int Rank(int key, int[] a)
        {
            int lo = 0;
            int hi = a.Length;
            while(lo<hi)
            {
                int mid = lo + (hi - lo) / 2;
                if (key < a[mid]) hi = mid - 1;
                else if (key > a[mid]) lo = mid + 1;
                else return mid;
            }
            return -1;
        }

        private static void TestRank()
        {
            int[] ints = StdIn.ReadAllInts();
            Array.Sort(ints);
            while (!StdIn.IsEmpty())
            {
                int key = StdIn.ReadInt();
                if (Rank(key, ints) < 0)
                    StdOut.Println(key); //如果不在名单里 则打印
            }
        }
        static void Main(string[] args)
        {
            Queue<string> q = new Queue<string>();
            Bag<string> b = new Bag<string>();
            while (!StdIn.IsEmpty())
            {
                string item = StdIn.ReadString();
                b.Add(item);
                if (!item.Equals("-"))
                    q.Enqueue(item);
                else if (!q.IsEmpty)
                    StdOut.Print(q.Dequeue() + " ");
            }

            foreach (var item in b)
                StdOut.Print(item + " ");
        }
    }
}

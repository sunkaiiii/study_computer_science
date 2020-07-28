using StandardLibraries;
using System;
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
        static void Main(string[] args)
        {
            int n = 3;
            double[] probabilities = { 0.5, 0.3, 0.1, 0.1 };
            int[] frequencies = { 5, 3, 1, 1 };
            string[] a = "A B C D E F G".Split(" ");

            for (int i = 0; i < n; i++)
            {
                StdOut.Printf("{0} ", StdRandom.Uniform(100));
                StdOut.Printf("{0} ", StdRandom.Uniform(10.0, 99.0));
                StdOut.Printf("{0} ", StdRandom.Bernoulli(0.5));
                StdOut.Printf("{0} ", StdRandom.Gaussian(9.0, 0.2));
                StdOut.Printf("{0} ", StdRandom.Discrete(probabilities));
                StdOut.Printf("{0} ", StdRandom.Discrete(frequencies));
                StdOut.Printf("{0} ", StdRandom.Uniform(100000));
                StdRandom.Shuffle(a);
                foreach (string s in a)
                    StdOut.Print(s);
                StdOut.Println();
            }
        }
    }
}

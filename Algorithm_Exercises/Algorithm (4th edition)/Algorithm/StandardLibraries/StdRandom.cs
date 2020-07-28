using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;

namespace StandardLibraries
{
    public static class StdRandom
    {
        private static int seed = CurrentTimeMillis();
        private static Random random=new Random(seed);
        private static readonly DateTime Jan1st1970 = new DateTime
    (1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);

        public static int CurrentTimeMillis()
        {
            return (int)(DateTime.UtcNow - Jan1st1970).TotalMilliseconds;
        }

        public static void  SetSeed(int s)
        {
            seed = s;
            random = new Random(seed);
        }

        public static double Uniform() => random.NextDouble();

        public static int Uniform(int n) => random.Next(n);

        public static int Uniform(int a, int b) => a + Uniform(b - a);

        public static double Uniform(double a, double b) => a + Uniform() * (b - a);

        public static bool Bernoulli(double p) => Uniform() < p;

        public static bool Bernoulli() => Bernoulli(0.5);

        public static double Gaussian()
        {
            double r, x, y;
            do
            {
                x = Uniform(-1.0, 1.0);
                y = Uniform(-1.0, 1.0);
                r = x * x + y * y;
            } while (r >= 1 || r == 0);
            return x * Math.Sqrt(-2 * Math.Log(r) / r);
        }

        public static double Gaussian(double mu, double sigma) => mu + sigma * Gaussian();

        public static int Geometric(double p) => (int)Math.Ceiling(Math.Log(Uniform()) / Math.Log(1.0 - p));

        public static int Poisson(double lambda)
        {
            int k = 0;
            double p = 1.0;
            double expLambda = Math.Exp(-lambda);
            do
            {
                ++k;
                p *= Uniform();
            } while (p >= expLambda);
            return k - 1;
        }

        public static double Pareto() => Pareto(1.0);

        public static double Pareto(double alpha) => Math.Pow(1 - Uniform(), -1.0 / alpha) - 1.0;

        public static double Cauchy() => Math.Tan(Math.PI * (Uniform() - 0.5));

        public static int Discrete(double[] probabilities)
        {
            double epsilon = 1.0e-14;
            double sum = 0.0;
            for(int i = 0; i < probabilities.Length; ++i)
            {
                sum += probabilities[i];
            }
            if (sum > 1.0 + epsilon || sum < 1.0 - epsilon)
                throw new Exception("sum of array entries does not approximately equal 1.0: " + sum);

            while (true)
            {
                double r = Uniform();
                sum = 0.0;
                for(int i = 0; i < probabilities.Length; ++i)
                {
                    sum += probabilities[i];
                    if (sum > r) return i;
                }
            }
        }

        public static int Discrete(int[] frequencies)
        {
            long sum = 0;
            for(int i=0;i<frequencies.Length;++i)
            {
                sum += frequencies[i];
            }
            if (sum == 0)
                throw new Exception("at least one array entry must be positive");
            if (sum >= int.MaxValue)
                throw new Exception("sum of frequencies overflows an int");
            double r = Uniform((int)sum);
            sum = 0;
            for(int i=0;i<frequencies.Length;++i)
            {
                sum += frequencies[i];
                if (sum > r)
                    return i;
            }
            return -1;
        }

        public static double Exp(double lambda) => -Math.Log(1 - Uniform()) / lambda;

        public static void Shuffle(object[] a)
        {
            ValidateNotNull(a);
            int n = a.Length;
            for(int i=0;i<n;++i)
            {
                int r = i + Uniform(n - i);
                object temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }
        public static void Shuffle(double[] a)
        {
            ValidateNotNull(a);
            int n = a.Length;
            for (int i = 0; i < n; i++)
            {
                int r = i + Uniform(n - i);    
                double temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static void Shuffle(int[] a)
        {
            ValidateNotNull(a);
            int n = a.Length;
            for (int i = 0; i < n; i++)
            {
                int r = i + Uniform(n - i);     // between i and n-1
                int temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static void Shuffle(char[] a)
        {
            ValidateNotNull(a);
            int n = a.Length;
            for (int i = 0; i < n; i++)
            {
                int r = i + Uniform(n - i);     // between i and n-1
                char temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static void Shuffle(object[] a, int lo, int hi)
        {
            ValidateNotNull(a);
            ValidateSubarrayIndices(lo, hi, a.Length);

            for (int i = lo; i < hi; i++)
            {
                int r = i + Uniform(hi - i);     // between i and hi-1
                Object temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static void Shuffle(double[] a, int lo, int hi)
        {
            ValidateNotNull(a);
            ValidateSubarrayIndices(lo, hi, a.Length);

            for (int i = lo; i < hi; i++)
            {
                int r = i + Uniform(hi - i);     // between i and hi-1
                double temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static void Shuffle(int[] a, int lo, int hi)
        {
            ValidateNotNull(a);
            ValidateSubarrayIndices(lo, hi, a.Length);

            for (int i = lo; i < hi; i++)
            {
                int r = i + Uniform(hi - i);     // between i and hi-1
                int temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
        }

        public static int[] Permutation(int n)
        {
            int[] perm = new int[n];
            for (int i = 0; i < n; i++)
                perm[i] = i;
            Shuffle(perm);
            return perm;
        }

        public static int[] Permutation(int n, int k)
        {
            int[] perm = new int[k];
            for (int i = 0; i < k; i++)
            {
                int r = Uniform(i + 1);    // between 0 and i
                perm[i] = perm[r];
                perm[r] = i;
            }
            for (int i = k; i < n; i++)
            {
                int r = Uniform(i + 1);    // between 0 and i
                if (r < k) perm[r] = i;
            }
            return perm;
        }
        private static void ValidateNotNull(object x)
        {
            if (x == null)
            {
                throw new Exception("argument is null");
            }
        }

        private static void ValidateSubarrayIndices(int lo, int hi, int length)
        {
            if (lo < 0 || hi > length || lo > hi)
            {
                throw new Exception("subarray indices out of bounds: [" + lo + ", " + hi + ")");
            }
        }
    }
}

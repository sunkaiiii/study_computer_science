using System;
using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace Chapter5.StringSearch
{
    //Numerics.cs
    //Author: v-bessonov https://github.com/v-bessonov
    //references on https://github.com/v-bessonov/Algorithms-NET/blob/567884f062cd81830dbe039b8e61dc625fa286dc/Algorithms.Core/Helpers/Numerics.cs
    public class Numerics
    {
        private static List<int> _primes;

        public static long Prime(long bound1, long bound2)
        {
            var randomLong = GetNextInt64(bound1, bound2);
            var prime = 0L;
            // bool isPrime = true;
            for (var i = randomLong; i <= bound2; i++)
            {
                var isPrime = true; // Move initialization to here
                for (long j = 2; j < i; j++) // you actually only need to check up to sqrt(i)
                {
                    if (i % j == 0) // you don't need the first condition
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                {
                    prime = i;
                    break;
                }
                // isPrime = true;
            }
            return prime;
        }


        public static List<long> Primes(long bound1, long bound2)
        {

            var primes = new List<long>();
            // bool isPrime = true;
            for (var i = bound1; i <= bound2; i++)
            {
                var isPrime = true; // Move initialization to here
                for (long j = 2; j < i; j++) // you actually only need to check up to sqrt(i)
                {
                    if (i % j == 0) // you don't need the first condition
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                {
                    primes.Add(i);
                }
                // isPrime = true;
            }
            return primes;
        }

        public static long GetNextInt64(long low, long hi)
        {
            var rng = new RNGCryptoServiceProvider();
            if (low >= hi)
                throw new ArgumentException("low must be < hi");
            var buf = new byte[8];

            //Generate a random double
            rng.GetBytes(buf);
            var num = Math.Abs(BitConverter.ToDouble(buf, 0));

            //We only use the decimal portion
            num = num - Math.Truncate(num);

            //Return a number within range
            return (long)(num * (hi - (double)low) + low);
        }

        public static long Prime()
        {
            var bytes = new byte[sizeof(long)];
            var gen = new RNGCryptoServiceProvider();
            var prime = 0L;
            while (prime <= 0L)
            {
                gen.GetBytes(bytes);
                prime = BitConverter.ToInt64(bytes, 0);
            }
            return prime;
        }

        //public long Prime(long num)
        //{

        //    var t = Math.Floor(2.52*Math.Sqrt(num)/Math.Log(num));

        //    return Enumerable.Range(0, (int) t).Aggregate(
        //        Enumerable.Range(2, num - 1).ToList(),
        //        (result, index) =>
        //        {
        //            var bp = result[index];
        //            var sqr = bp*bp;
        //            result.RemoveAll(i => i >= sqr && i%bp == 0);
        //            return result;

        //        }
        //        );
        //}

        public static long ApproximateNthPrime(long nn)
        {
            var n = (double)nn;
            double p;
            if (nn >= 7022)
            {
                p = n * Math.Log(n) + n * (Math.Log(Math.Log(n)) - 0.9385);
            }
            else if (nn >= 6)
            {
                p = n * Math.Log(n) + n * Math.Log(Math.Log(n));
            }
            else if (nn > 0)
            {
                p = new[] { 2, 3, 5, 7, 11 }[nn - 1];
            }
            else
            {
                p = 0;
            }
            return (long)p;
        }

        // Find all primes up to and including the limit
        public static bool[] SieveOfEratosthenes(long limit)
        {
            var bits = new bool[limit + 1];
            for (var i = 0; i < bits.Length; i++)
            {
                bits[i] = true;
            }
            bits[0] = false;
            bits[1] = false;
            for (var i = 0; i * i <= limit; i++)
            {
                if (bits[i])
                {
                    for (var j = i * i; j <= limit; j += i)
                    {
                        bits[j] = false;
                    }
                }
            }
            return bits;
        }

        public static BitArray SieveOfSundaram(int limit)
        {
            limit /= 2;
            var bits = new BitArray(limit + 1, true);
            for (var i = 1; 3 * i + 1 < limit; i++)
            {
                for (var j = 1; i + j + 2 * i * j <= limit; j++)
                {
                    bits[i + j + 2 * i * j] = false;
                }
            }
            return bits;
        }

        public static List<long> GeneratePrimesSieveOfSundaram(long n)
        {
            var limit = ApproximateNthPrime(n);
            var bits = SieveOfEratosthenes(limit);
            var primes = new List<long> { 2 };
            for (long i = 1, found = 1; 2 * i + 1 <= limit && found < n; i++)
            {
                if (bits[i])
                {
                    primes.Add(2 * i + 1);
                    found++;
                }
            }
            return primes;
        }

        public static List<int> GeneratePrimesSieveOfSundaram(int n)
        {
            var limit = ApproximateNthPrime(n);
            var bits = SieveOfSundaram(limit);
            var primes = new List<int> { 2 };
            for (int i = 1, found = 1; 2 * i + 1 <= limit && found < n; i++)
            {
                if (!bits[i]) continue;
                primes.Add(2 * i + 1);
                found++;
            }
            return primes;
        }

        public static int ApproximateNthPrime(int nn)
        {
            var n = (double)nn;
            double p;
            if (nn >= 7022)
            {
                p = n / Math.Log(n);
                //p = n * Math.Log(n) + n * (Math.Log(Math.Log(n)) - 0.9385);
            }
            else if (nn >= 6)
            {
                p = n * Math.Log(n) + n * Math.Log(Math.Log(n));
            }
            else if (nn > 0)
            {
                p = new[] { 2, 3, 5, 7, 11 }[nn - 1];
            }
            else
            {
                p = 0;
            }
            return (int)p;
        }

        public static BitArray SieveOfEratosthenes(int limit)
        {
            var bits = new BitArray(limit + 1, true)
            {
                [0] = false,
                [1] = false
            };
            for (var i = 0; i * i <= limit; i++)
            {
                if (!bits[i]) continue;
                for (var j = i * i; j <= limit; j += i)
                {
                    bits[j] = false;
                }
            }
            return bits;
        }

        public static int GetPrime()
        {
            if (_primes == null)
            {
                _primes = GeneratePrimesSieveOfSundaram(int.MaxValue);
            }
            var length = _primes.Count;
            var random = new Random();
            return _primes[random.Next(length)];
        }
    }
}

using StandardLibraries;
using System;

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
            Scanner scanner = new Scanner(Console.In);
            Console.WriteLine(scanner.HasNext());
            Console.WriteLine(scanner.ReadLong());
            Console.WriteLine(scanner.HasNext());
            Console.WriteLine(scanner.ReadLong());
            Console.WriteLine(scanner.HasNext());
            //Console.WriteLine(Gcd(64, 24));
        }
    }
}

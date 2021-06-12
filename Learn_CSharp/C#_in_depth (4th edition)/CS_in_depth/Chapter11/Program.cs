using System;
using System.Collections.Generic;
using System.Linq;

namespace Chapter11
{
    class Program
    {
        //元组的使用
        static (int min, int max) MinMax(IEnumerable<int> source)
        {
            int max = source.Max();
            int min = source.Min();
            return (min, max);
        }
        static void Main(string[] args)
        {
            int[] values = { 2, 7, 3, -5, 1, 0, 10 };
            var extremes = MinMax(values);
            Console.WriteLine(extremes.min);
            Console.WriteLine(extremes.max);
        }
    }
}

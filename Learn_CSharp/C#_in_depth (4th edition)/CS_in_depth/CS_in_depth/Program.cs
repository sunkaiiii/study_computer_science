using System;
using System.Collections.Generic;

namespace CS_in_depth
{
    
    class Program
    {
        //生成整形迭代器
        static IEnumerable<int> CreateSimpleIterator()
        {
            yield return 10;
            for (int i = 0; i < 3; i++)
            {
                yield return i; 
            }
            yield return 20;
        }

        //延迟执行的重要性
        static IEnumerable<int> Fibonacci()
        {
            int current = 0;
            int next = 1;
            while (true)
            {
                yield return current;
                int oldCurrent = current;
                current = next;
                next = next + oldCurrent;
            }
        }

        static void PrintType<T>()
        {
            Console.WriteLine("typeof(T) = {0}", typeof(T));
            Console.WriteLine("typeof(List<T>) = {0}", typeof(List<T>));
        }

        static void Main(string[] args)
        {
            PrintType<string>(); 
            PrintType<int>();

            foreach (int i in CreateSimpleIterator())
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("Print fibonacci");
            foreach(var value in Fibonacci())
            {
                Console.WriteLine(value);
                if (value > 1000)
                {
                    break;
                }
            }
        }
    }
}

using System;

namespace Chapter4
{
    class Program
    {
        static void Add(dynamic d)
        {
            Console.WriteLine(d + d);
        }
        static void Main(string[] args)
        {
            //使用不同的值调用方法
            Add("Text");
            Add(10);
            Add(TimeSpan.FromMinutes(45));
        }
    }
}

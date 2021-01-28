using System;

namespace Chapter9
{
    class Program
    {
        //C# 允许对ref/out类型的重载
        static void Add(String s)
        {

        }

        static void Add(ref String s)
        {

        }

        //使用泛型来实现类的交换
        public static void Swap<T>(ref T a, ref T b)
        {
            T t = b;
            b = a;
            a = t;
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

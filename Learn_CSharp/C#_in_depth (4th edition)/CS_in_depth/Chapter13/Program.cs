using System;
using System.Collections.Generic;

namespace Chapter13
{
    class Program
    {
        private int value;
        static void Main(string[] args)
        {
            //多个ref参数使用同一个变量
            int x = 5;
            IncrementAndDouble(ref x, ref x);
            Console.WriteLine(x);

            //使用ref局部变量为一个对象的字段取别名
            var obj = new Program();
            ref int tmp = ref obj.value;
            tmp = 10;
            Console.WriteLine(obj.value);

            x = 0;
            InParameter(x, () => x++);
            Console.WriteLine(x);
        }

        static void IncrementAndDouble(ref int p1, ref int p2)
        {
            p1++;
            p2 *= 2;
        }

        //使用ref来计算序列中奇数和偶数的个数
        static (int even, int odd) CountEvenAndOdd(IEnumerable<int> values)
        {
            var result = (even: 0, odd: 0);
            foreach(var value in values)
            {
                ref int counter = ref (value & 1) == 0 ? ref result.even : ref result.odd;
                counter++;
            }
            return result;
        }

        //in参数不可变性的例外
        static void InParameter(in int p, Action action)
        {
            Console.WriteLine("Start of InParameter method");
            Console.WriteLine($"p = {p}");
            action();
            Console.WriteLine($"p = {p}");
        }
    }
}

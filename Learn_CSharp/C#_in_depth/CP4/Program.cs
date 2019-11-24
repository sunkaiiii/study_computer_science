using System;

namespace CP4
{
    class Program
    {
        static void Display(Nullable<int> x)
        {
            if(x.HasValue)
            {
                Console.WriteLine("Value: {0}", x.Value);
                Console.WriteLine("Explicit conversion: {0}", (int)x); //显式转换
            }
            Console.WriteLine("GetValueOrDefault(): {0}", x.GetValueOrDefault()); //无参数的
            Console.WriteLine("GetValueOrDefaul(10): {0}", x.GetValueOrDefault(10));
            Console.WriteLine("ToString(): \"{0}\"", x.ToString());
            Console.WriteLine("GetHashCode(): {0}", x.GetHashCode()); //重载了这两个方法，使得当里面没有值的时候返回0
            Console.WriteLine();
        }

        static void PrintValuesAsInt32(object o)
        {
            int? nullable = o as int?; //仅需一步就可以安全的将任意引用转换为值，但是他的速度往往会比is操作符慢几乎20倍。小心这个惊人的性能陷阱。
            Console.WriteLine(nullable.HasValue ? nullable.Value.ToString() : "null");
        }

        static void TryParse(string text)
        {
            int? parsed = int.Parse(text);
            if(parsed!=null)
            {
                Console.WriteLine("Parsed to {0}", parsed.Value);
            }
            else
            {
                Console.WriteLine("Couldn't parse");
            }

        }

        static void Main(string[] args)
        {
            Nullable<int> x = 5;
            x = new Nullable<int>(5);
            Console.WriteLine("Instance with value:");
            Display(x);

            x = new Nullable<int>();
            Console.WriteLine("Instance without value:");
            Display(x);


            //可空类型的拆箱和装箱行为
            Nullable<int> nullalbe = 5;
            object boxed = nullalbe; //装箱成有值的实例
            Console.WriteLine(boxed.GetType());
            int normal = (int)boxed;//拆箱成有值的变量
            Console.WriteLine(normal);
            nullalbe = (Nullable<int>)boxed;//拆箱成可空变量
            Console.WriteLine(nullalbe);
            nullalbe = new Nullable<int>();
            boxed = nullalbe;//装箱成一个没有值的可空变量的实例
            Console.WriteLine(boxed == null);
            nullalbe = (Nullable<int>)boxed;
            Console.WriteLine(nullalbe.HasValue);

            //C# 2对于可空类型的语法糖
            Person turing = new Person("Alan Turing", new DateTime(1912, 6, 23), new DateTime(1954, 6, 7));
            Person kunth = new Person("Donald Knuth", new DateTime(1938, 1, 10), null);

            //对可空类型使用as操作符
            PrintValuesAsInt32(5);
            PrintValuesAsInt32("some string");

            //可空类型对于parse的使用
            TryParse("123");
            
        }
    }
}

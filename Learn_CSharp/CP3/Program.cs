using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace CP3
{
    class Program
    {
        //使用泛型类
        static Dictionary<string, int> CountWords(string text)
        {
            Dictionary<string,int> frequencies = new Dictionary<string, int>();
            string[] words = Regex.Split(text, @"\W+");
            foreach(string word in words)
            {
                if(frequencies.ContainsKey(word))
                {
                    frequencies[word]++;
                }
                else
                {
                    frequencies[word] = 1;
                }
            }
            return frequencies;
        }

        //List<T>.ConvertAll<TOutput>泛型方法使用
        static double TakeSquareRoot(int x)
        {
            return Math.Sqrt(x);
        }
        private static void ConvertList()
        {
            List<int> integers = new List<int>();
            integers.Add(1);
            integers.Add(2);
            integers.Add(3);
            integers.Add(4);
            Converter<int, double> converter = TakeSquareRoot; //创建委托实例
            List<double> doubles = integers.ConvertAll<double>(converter);
            foreach(double d in doubles)
            {
                Console.WriteLine(d);
            }
        }

        //在普通类中实现泛型方法
        static List<T> MakeList<T> (T first, T second)
        {
            List<T> list = new List<T>();
            list.Add(first);
            list.Add(second);
            return list;
        }

        //以泛型方式将一个给定的值和默认值进行比较
        static int CompareToDefault<T>(T value)
                where T : IComparable<T>
        {
            return value.CompareTo(default(T));
        }

        //使用泛型直接比较
        static bool AreReferencesEqual<T>(T first, T second)
            where T : class
        {
            return first == second;  //限定引用类型，可以直接比较引用
        }

        static void Main(string[] args)
        {
            //使用CountWords方法
            string text = @"Do you like green eggs and ham?
                            I do not like them, Sam-I-am.
                            I do not like green eggs and ham.";
            Dictionary<string, int> frequencies = CountWords(text);
            foreach(KeyValuePair<string,int> entry in frequencies)
            {
                string word = entry.Key;
                int frequency = entry.Value;
                Console.WriteLine("{0}: {1}", word, frequency);
            }

            ConvertList();
            //使用自定义的泛型方法
            List<string> list = MakeList<string>("Line 1", "Line 2");
            foreach(var x in list)
            {
                Console.WriteLine(x);
            }

            //泛型比较
            string name = "Jon";
            string intro1 = "My name is " + name; 
            string intro2 = "My name is " + name;
            Console.WriteLine(intro1 == intro2);//使用string的重载运算符进行比较
            Console.WriteLine(AreReferencesEqual(intro1, intro2));//编译器无法知道有什么重载类型，返回false

            //使用泛型方法，创建实现的泛型类
            Pair<int, string> pair = Pair.Of(10, "value");
        }
    }
}

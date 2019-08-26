using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
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

        //证明不同的封闭类型具有不同的静态字段
        class TypeField<T>
        {
            public static string filed;
            public static void PrintField()
            {
                Console.WriteLine(filed + ": " + typeof(T).Name);
            }
        }

        class Outer<T>
        {
            public class Inner<U,V>
            {
                static Inner()
                {
                    Console.WriteLine("Outer<{0}>.Inner<{1},{2}>", typeof(T).Name, typeof(U).Name, typeof(V).Name);
                }
                public static void DummyMethod() { }
                public static void Dummy() { Console.WriteLine(typeof(T)); }
            }
        }


        //一个完整的泛型枚举--从0枚举到9
        class CountingEnumerable: IEnumerable<int>
        {

            IEnumerator IEnumerable.GetEnumerator() //隐式实现IEnumerable<T>
            {
                return GetEnumerator();
            }

            public IEnumerator<int> GetEnumerator() //显示实现IEnumerable
            {
                return new CountingEnumerator();
            }
        }

        class CountingEnumerator : IEnumerator<int>
        {
            int current = -1;
            public bool MoveNext()
            {
                current++;
                return current < 10;
            }
            public int Current { get { return current; } } //隐式实现IEnumerator<T>.Current
            object IEnumerator.Current { get { return Current; } } //显示实现IEnumerator.Current
            public void Reset()
            {
                current = -1;
            }
            public void Dispose() { }
        }

        static void DemonstrateTypeof<X>()
        {
            Console.WriteLine(typeof(X));
            Console.WriteLine(typeof(List<>));
            Console.WriteLine(typeof(Dictionary<,>)); //尖括号要保留，告诉编译器查找具有两个类型参数的类型
            Console.WriteLine(typeof(List<X>));
            Console.WriteLine(typeof(Dictionary<string, X>));
            Console.WriteLine(typeof(List<long>));
            Console.WriteLine(typeof(Dictionary<long, Guid>));
        }

        //通过反射来获取和调用泛型方法
        public static void PrintTypeParameter<T>()
        {
            Console.WriteLine(typeof(T));
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

            //封闭类型的静态字段
            TypeField<int>.filed = "First";
            TypeField<string>.filed = "Second";
            TypeField<DateTime>.filed = "Third";
            TypeField<int>.PrintField();
            TypeField<string>.PrintField();
            TypeField<DateTime>.PrintField();

            //嵌套泛型类型的静态构造函数
            //第一次调用dummy的时候，不论是什么类型，都会导致inner类型初始化
            //不同类型的实参被看作一个不同的封闭类型
            //相同的封闭类型，只会初始化一次
            Outer<int>.Inner<string, DateTime>.DummyMethod();
            Outer<string>.Inner<int, int>.DummyMethod();
            Outer<object>.Inner<string, object>.DummyMethod();
            Outer<string>.Inner<string, object>.DummyMethod();
            Outer<object>.Inner<object, string>.DummyMethod();
            Outer<string>.Inner<int, int>.DummyMethod(); //封闭成员已经在第二句执行过一次静态构造函数，所以这块不会打印

            //泛型枚举
            CountingEnumerable counter = new CountingEnumerable();
            foreach(int x in counter)
            {
                Console.WriteLine(x);
            }

            //对参数类型使用typeof操作符
            DemonstrateTypeof<int>();

            //获取泛型和已构造Type对象的各种方式
            string listTypeName = "System.Collections.Generic.List`1";
            Type defByName = Type.GetType(listTypeName);
            //这将会输出四个true，证明不论怎样获取一个特定对象类型的引用，都只涉及一个这样的对象。
            Type closedByName = Type.GetType(listTypeName + "[System.String]");
            Type closedByMethod = defByName.MakeGenericType(typeof(string));
            Type closedByTypeof = typeof(List<string>);
            Console.WriteLine(closedByMethod == closedByName);
            Console.WriteLine(closedByName == closedByTypeof);
            Type defByTypeof = typeof(List<>);
            Type defByMethod = closedByName.GetGenericTypeDefinition();
            Console.WriteLine(defByMethod == defByName);
            Console.WriteLine(defByName == defByTypeof);

            //通过反射来获取调用泛型方法
            Type type = typeof(Outer<int>.Inner<int, int>);
            MethodInfo definition = type.GetMethod("Dummy");
            definition.Invoke(null,null);

        }
    }
}

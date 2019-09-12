using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CP6
{
    //在c# 1中，需要使用将近40行来实现迭代器
    class InterationSample
    {
        public object[] values;
        public int startingPoint;

        public InterationSample(object[] values, int startingPoint)
        {
            this.values = values;
            this.startingPoint = startingPoint;
        }

        public IEnumerator GetEnumerator()
        {
            //return new IterationSampleIterator(this);
            //利用C# 2和yiled return来迭代
            for (int index = 0; index < values.Length; index++)
            {
                yield return values[(index + startingPoint) % values.Length];
            }
        }
        //显示迭代器以及其调用者之间的调用序列
        static readonly string Padding = new string(' ', 30);
        public static IEnumerable<int> CreateEnumerable()
        {
            Console.WriteLine("{0} Start of Create Enumerable()", Padding);
            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine("{0} About to yield {1}", Padding, i);
                yield return i;
                Console.WriteLine("{0} After yield", Padding);
            }
            Console.WriteLine("{0} Yielding final value", Padding);
            yield return -1;
            Console.WriteLine("{0} End of CreateEnumerable()", Padding); //这句是不会执行的
        }

        public static IEnumerable<int> CountWithTimeLimit(DateTime limit)
        {
            //finally代码块可以和yield break配合使用
            try
            {
                for (int i = 1; i <= 100; i++)
                {
                    if (DateTime.Now >= limit)
                    {
                        yield break; //停止迭代运行
                    }
                    yield return i;
                }
            }
            finally
            {
                Console.WriteLine("Stopping!!!"); //不管循环是否结束，都会执行。
            }
        }

        public static IEnumerable<string> ReadLines(Func<TextReader> provider)
        {
            using (TextReader reader = provider())
            {
                string line;
                while((line=reader.ReadLine())!=null)
                {
                    yield return line;
                }
            }
        }

        public static IEnumerable<string> ReadLines(string filename)
        {
            return ReadLines(filename, Encoding.UTF8);
        }
        public static IEnumerable<string> ReadLines(string filename,Encoding encoding)
        {
            return ReadLines(delegate { return File.OpenText(filename); });
        }

        //使用迭代器块实现LINQ的where方法
        public static IEnumerable<T> Where<T> (IEnumerable<T> source,Predicate<T> predicate)
        {
            if(source == null|| predicate==null)
            {
                throw new ArgumentNullException();
            }
            return WhereImpl(source, predicate);
        }

        private static IEnumerable<T> WhereImpl<T> (IEnumerable<T> source,Predicate<T> predicate)
        {
            foreach(T item in source)
            {
                if(predicate(item))
                {
                    yield return item; //惰性求值
                }
            }
        }
    }
}

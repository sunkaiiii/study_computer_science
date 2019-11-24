using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace CP14
{
    static class Helper
    {
        //动态的对任意元素的序列进行求和
        public static T DynamicSum<T>(this IEnumerable<T> source)
        {
            dynamic total = default(T);
            foreach (T element in source)
            {
                total = (T)(total + element);
            }
            return total;
        }

        //使用动态分发有效的为不同的类型提供计数方法
        private static int CountImpl<T>(ICollection<T> collection)
        {
            return collection.Count;
        }

        private static int CountImpl(ICollection collection)
        {
            return collection.Count;
        }

        private static int CountImpl(string text)
        {
            return text.Length;
        }

        private static int CountImpl(IEnumerable collection)
        {
            int count = 0;
            foreach (object item in collection)
            {
                count++;
            }
            return count;
        }

        public static void PrintCount(IEnumerable collection)
        {
            dynamic d = collection;
            int count = CountImpl(d);
            Console.WriteLine(count);
        }

    }
}

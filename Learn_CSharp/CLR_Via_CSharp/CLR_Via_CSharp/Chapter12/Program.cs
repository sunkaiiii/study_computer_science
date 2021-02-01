using System;
using System.Collections.Generic;

namespace Chapter12
{
    //一个部分指定的开放类型
    internal sealed class DictionaryStringKey<TValue> : Dictionary<String, TValue>
    {

    }

    class Program
    {
        //当前CLR还不支持泛型类型变量作为操作数使用
        //private static T Sum<T>(T num)where T : struct
        //{
        //    T sum = default(T);
        //    for (T n = default(T); n < num; n++)
        //        sum += n;
        //    return sum;
        //}

        static void Main(string[] args)
        {
            object o = null;
            //开放类型，有两个未指明的类型参数
            Type t = typeof(Dictionary<,>);

            o = CreateInstance(t);
            Console.WriteLine();


            //DictionaryStringKey是开放类型，有1个类型参数
            t = typeof(DictionaryStringKey<>);

            o = CreateInstance(t);
            Console.WriteLine();

            //DictionaryStringKey<Guid>是封闭类型
            t = typeof(DictionaryStringKey<Guid>);
            o = CreateInstance(t);
            Console.WriteLine(" 对象类型 = " + o.GetType());
        }

        private static object CreateInstance(Type t)
        {
            object o = null;
            try
            {
                o = Activator.CreateInstance(t);
                Console.Write("已创建{0}的实例", t.ToString());
            }catch(ArgumentException e)
            {
                Console.WriteLine(e.Message);
            }
            return o;
        }
    }
}

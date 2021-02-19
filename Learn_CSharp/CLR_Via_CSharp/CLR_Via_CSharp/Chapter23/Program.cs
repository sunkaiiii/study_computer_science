using System;
using System.Collections.Generic;
using System.Reflection;

namespace Chapter23
{
    class Program
    {
        private const BindingFlags c_bf = BindingFlags.FlattenHierarchy | BindingFlags.Instance | BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic;
        private static void Show(string s)
        {
            Console.WriteLine("Heap size={0,12:N0}-{1}", GC.GetTotalMemory(true), s);
        }
        static void Main(string[] args)
        {
            Type openType = typeof(Dictionary<,>);

            //使用TKey=String,Tvalue=Int32封闭泛型类型
            Type closedType = openType.MakeGenericType(typeof(string), typeof(int));
            //构造封闭类型实例
            object o = Activator.CreateInstance(closedType);
            Console.WriteLine(o.GetType());

            //显示在任何反射之前堆的大小
            Show("Before doing anything");
            //为MSCorLib.dll中的所有方法构建methodInfo缓存
            List<MethodBase> methodInfos = new List<MethodBase>();
            foreach(Type t in typeof(object).Assembly.GetExportedTypes())
            {
                if (t.IsGenericTypeDefinition)
                    continue;
                MethodBase[] mb = t.GetMethods(c_bf);
                methodInfos.AddRange(mb);
            }
            //显示当绑定所有方法后，方法的个数和堆的大小
            Console.WriteLine("# of methods={0:N0}", methodInfos.Count);
            Show("After bulding cache of MethodInfo objects");

            //为所有对象构建RuntimeMethodHandle缓存
            List<RuntimeMethodHandle> methodHandles = methodInfos.ConvertAll<RuntimeMethodHandle>(mb => mb.MethodHandle);
            Show("Holding MethodInfo and RuntimeMethodHandle cache");

            GC.KeepAlive(methodInfos); //组织缓存被过早的回收
            methodInfos = null; //现在允许缓存垃圾回收

            Show("After freeing MethodInfo objects");

            methodInfos = methodHandles.ConvertAll<MethodBase>(rmh => MethodBase.GetMethodFromHandle(rmh));
            Show("Size of heap after re-creating MethodInfo objects");
            GC.KeepAlive(methodHandles);
            GC.KeepAlive(methodInfos);

            methodHandles = null;
            methodInfos = null;
            Show("After freeing methodinfos and runtimeMethodHandles");
        }
    }
}

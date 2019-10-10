using IronPython.Hosting;
using Microsoft.Scripting.Hosting;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace CP14
{
    class Program
    {
        private static bool AddConditionallyImpl<T>(IList<T> list, T item)
        {
            if(list.Count<10)
            {
                list.Add(item);
                return true;
            }
            return false;
        }

        public static bool AddConditionally(dynamic list, dynamic item)
        {
            return AddConditionallyImpl(list, item); //动态调用辅助方法
        }

        //鸭子类型访问Count属性
        static void PrintCount(IEnumerable collection)
        {
            dynamic d = collection;
            int count = d.Count;
            Console.WriteLine(count);
        }

        //方法重载和动态值
        static void Execute(string x)
        {
            Console.WriteLine("String overload");
        }

        static void Execute(dynamic x)
        {
            Console.WriteLine("Dynamic overload");
        }

        static void Execute(dynamic x,string y)
        {
            Console.WriteLine("dynamic, string");
        }

        static void Execute(dynamic x,object y)
        {
            Console.WriteLine("dynamic, object");
        }

        //类层次当中的动态重载决策
        class Base
        {
            public void Execute(object x)
            {
                Console.WriteLine("object");
            }
        }

        class Derived:Base
        {
            public void Execute(string x)
            {
                Console.WriteLine("string");
            }
        }

        static void Main(string[] args)
        {
            //使用dynamic遍历列表，连接字符串
            dynamic items = new List<string> { "First", "Second", "Third" };
            dynamic valueToAdd = "!";
            foreach(dynamic item in items)
            {
                string result = item + valueToAdd;
                Console.WriteLine(result);
            }

            //使用IronPython动态加载其他动态语言
            ScriptEngine engine = Python.CreateEngine();
            engine.Execute("print 'hello world'");

            //使用ScriptScope在宿主和脚本之间传递信息
            ScriptScope scope = engine.CreateScope();
            scope.SetVariable("variable", 10);
            engine.ExecuteFile("HelloWorld.py", scope);
            Console.WriteLine(scope.GetVariable("text"));
            Console.WriteLine(scope.GetVariable("variable"));
            Console.WriteLine(scope.GetVariable("output"));

            //使用动态类型推断
            object list = new List<string> { "x", "y" };
            object item2 = "z";
            AddConditionally(list, item2);

            //使用动态扩展方法进行求值
            byte[] bytes = new byte[] { 1, 2, 3 };
            Console.WriteLine(bytes.DynamicSum());

            PrintCount(new BitArray(10));
            PrintCount(new HashSet<int> { 3, 5 });
            PrintCount(new List<int> { 1, 2, 3 });

            //使用动态分发
            Helper.PrintCount(new BitArray(5));
            Helper.PrintCount(new HashSet<int> { 1, 2 });
            Helper.PrintCount("ABC");
            Helper.PrintCount("ABCDEF".Where(c => c > 'B'));

            //测试方法重载和动态值
            dynamic text = "text";
            Execute(text); //打印string overload
            dynamic number = 10;
            Execute(number); //打印dynamic overload

            //单个类型中的动态重载决策
            dynamic d = 10;
            object otext = "text";
            Execute(d, otext); //打印dynamic, object

            //类层次当中的重载决策
            Base receiver = new Derived();
            dynamic dd = "text";
            receiver.Execute(dd); //打印object

            //动态类型的Lambda表达式
            //dynamic badMethodGroup = Console.WriteLine; //不能编译
            dynamic goodMethodGroup = (Action<string>)Console.WriteLine;
            //dynamic badLambda = y => y + 1; //不能编译
            dynamic goodLambda = (Func<int, int>)(y => y + 1);
            dynamic veryDynamic = (Func<dynamic, dynamic>)(d => d.SomeMethod());

            //查询动态元素集合
            var list2 = new List<dynamic> { 50, 5m, 5d };
            var query = from n2 in list2
                        where n2 > 4
                        select (n2 / 20) * 10;
            foreach(var item in query)
            {
                Console.WriteLine(item);
            }
        }
    }
}

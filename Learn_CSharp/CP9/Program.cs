using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq.Expressions;
using System.Reflection;

namespace CP9
{
    class Program
    {
        class Film
        {
            public string Name { get; set; }
            public int Year { get; set; }
        }

        delegate T MyFunc<T>(); //.NET 2.0中没有个Func<T>
        static void WriteResult<T>(MyFunc<T> function)
        {
            Console.WriteLine(function());
        }

        //多级类型推断
        static void ConvertTwice<TInput,TMiddle,TOutput>(TInput input,Converter<TInput,TMiddle> firstConversion, Converter<TMiddle,TOutput> secondConversion)
        {
            TMiddle middle = firstConversion(input);
            TOutput output = secondConversion(middle);
            Console.WriteLine(output);
        }

        //委托的返回类型影响了重载的选择
        static void Execute(Func<int> action)
        {
            Console.WriteLine("action returns an int: " + action());
        }

        static void Execute(Func<double> action)
        {
            Console.WriteLine("action returns a double:" + action());
        }

        static void Main(string[] args)
        {
            //使用匿名方法来创建委托实例
            Func<string, int> returnLength;
            returnLength = delegate (string text) { return text.Length; };
            Console.WriteLine(returnLength("Hello"));
            //冗长的第一个lambda表达式
            returnLength = (string text) => { return text.Length; };
            Console.WriteLine(returnLength("Hello"));
            //单一表达式作为主题
            returnLength = (string text) => text.Length;
            Console.WriteLine(returnLength("Hello"));
            //隐式类型的表达式
            returnLength = text => text.Length; //因为参数只有一个，所以圆括号同样可以省略
            Console.WriteLine(returnLength("Hello"));

            //使用lambda表达式来处理一个电影的列表
            var films = new List<Film>
            {
                new Film{Name="Jaws",Year=1975},
                new Film{Name="Singing in the rain",Year=1952},
                new Film{Name="Some like it Hot",Year=1959},
                new Film{Name="The wizard of Oz",Year=1939},
                new Film{Name="It's a wonderful life",Year=1946},
                new Film{Name="American Beauty",Year=1999},
                new Film{Name="The Usual Suspects",Year=1995},
                new Film{Name="High Fidelity",Year=2000}
            };
            Action<Film> print = film => Console.WriteLine("Name={0},Year={1}", film.Name, film.Year); //创建可用的列表打印委托
            films.ForEach(print);//打印原始列表
            films.FindAll(film => film.Year < 1960).ForEach(print); //创建过滤过的列表
            films.Sort((f1, f2) => string.Compare(f1.Name, f2.Name, StringComparison.Ordinal)); //对原始列表排序
            films.ForEach(print);

            //一个非常简单的表达式树
            Expression firstArg = Expression.Constant(2);
            Expression secondArg = Expression.Constant(3);
            Expression add = Expression.Add(firstArg, secondArg);
            Console.WriteLine(add);
            Func<int> compiled = Expression.Lambda<Func<int>>(add).Compile();
            Console.WriteLine(compiled());
            //使用Lambda表达式创建表达式树
            Expression<Func<int>> return5 = () => 5;
            compiled = return5.Compile();
            Console.WriteLine(compiled());

            //更为复杂的表达式树
            Expression<Func<string, string, bool>> expression = (x, y) => x.StartsWith(y, StringComparison.Ordinal);
            var predicateCompiled = expression.Compile();
            Console.WriteLine(predicateCompiled("First", "Second"));
            Console.WriteLine(predicateCompiled("First", "Fir"));

            //使用代码来构造一个方法调用表达式树
            MethodInfo method = typeof(string).GetMethod("StartsWith", new[] { typeof(string) });
            var target = Expression.Parameter(typeof(string), "x");
            var methodArg = Expression.Parameter(typeof(string), "y");
            Expression[] methodArgs = { methodArg };
            Expression call = Expression.Call(target, method, methodArgs); //从以上部件创建CallExpression

            var lambdaParameters = new[]{ target, methodArg };
            var lambda = Expression.Lambda<Func<string, string, bool>>(call, lambdaParameters);
            var lambdaCompiled = lambda.Compile();
            Console.WriteLine(lambdaCompiled("First", "Second"));
            Console.WriteLine(lambdaCompiled("First", "Fir"));

            //尝试推断匿名方法的返回类型
            WriteResult(delegate { return 5; }); //要求对T进行类型判断，在C# 2当中会报错

            //更为复杂的一种匿名推断的场景
            WriteResult(delegate //这里，int可以隐式推断到object，但是反过来不行。所以类型就为object
            {
                if (DateTime.Now.Hour < 12)
                {
                    return 10;
                }
                else
                {
                    return new object();
                }
            });

            ConvertTwice("Another string", text => text.Length, length => Math.Sqrt(length));

            //委托返回类型影响了重载的选择
            Execute(() => 1);
        }
    }
}

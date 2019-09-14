using System;
using System.Runtime.CompilerServices;
class Configuration { }
namespace cp7
{
    class Program
    {
        //C# 2独立的取值方法和赋值方法器
        string name;
        public string Name
        {
            get { return name; }
            private set
            {
                name = value;
            }
        }

        class Configuration { }

        [assembly: InternalsVisibleTo("FriendAssembly")]
        public class Source
        {
            internal static void InternalMethod() { }
            public static void PublicMethod() { }
        }


        static void Main(string[] args)
        {
            //使用全局命名空间别名来精准的设定想要的类型。
            Console.WriteLine("Hello World!");
            Console.WriteLine(typeof(Configuration));
            Console.WriteLine(typeof(global::Configuration));
            Console.WriteLine(typeof(global::cp7.Program));
            Source.InternalMethod(); //使用额外的访问去那先
            Source.PublicMethod();
        }
    }
}

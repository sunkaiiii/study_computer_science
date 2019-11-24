using System;

namespace CP2
{
    class Program
    {
        static void HandleDemoEvent(object sender, EventArgs e)
        {
            Console.WriteLine("Handled by HandleDemoEvent");
        }
        static void Main(string[] args)
        {
            //使用委托
            Person jon = new Person("Jon");
            Person tom = new Person("Tom");
            StringProcessor jonsVoice, tomsVoice, background; //创建3个委托实例
            jonsVoice = new StringProcessor(jon.Say);
            tomsVoice = new StringProcessor(tom.Say);
            background = new StringProcessor(Background.Note);
            jonsVoice("Hello, son");
            tomsVoice.Invoke("Hello,Daddy"); //一般情况下不需要显示调用。
            background("An airplane flies past");


            //C# 2中对于委托的改进
            //C# 1当中的写法
            EventHandler handler;
            handler = new EventHandler(HandleDemoEvent);
            handler(null, EventArgs.Empty);
            //C# 2中使用隐式委托实例
            handler = delegate (object sender, EventArgs e)
            {
                Console.WriteLine("Handled anonymously");
            };
            handler(null, EventArgs.Empty);
            //C# 2中使用匿名方法的简写形式
            handler = delegate
            {
                Console.WriteLine("Handled anonymously again");
            };
            handler(null, EventArgs.Empty);
            //C# 2使用委托的逆变性
            //.NET Core中不可用
            //MouseEventHandler mouseEventHandler = HandleDemoEvent;
            //mouseEventHandler(null, new MouseEventArgs(MouseButtons, None, 0, 0, 0, 0));

            //C# 3中，使用Func委托类型以及Lambda表达式的例子
            Func<int, int, string> func = (x, y) => (x * y).ToString();
            Console.WriteLine(func(5, 20));

            //C# 3中引入的匿名类型
            var jon2 = new { Name = "jon", Age = 31 };
            var tom2= new { Name = "Tom", Age = 4 };
            Console.WriteLine("{0} is {1}", jon2.Name, jon2.Age);
            Console.WriteLine("{0} is {1}", tom2.Name, tom2.Age);
            jon2 = tom2; //编译器根据声明的字段，推断出了他们具有相同的类型。所以可以使用赋值。

            //C# 4当中引入了动态类型
            dynamic o = "hello";
            Console.WriteLine(o.Length);
            o = new string[] { "hi", "there" };
            Console.WriteLine(o.Length);

            //C#2的可空类型
            int? x2 = null;
            x2 = 5;
            if (x2!=null)
            {
                int y = x2.Value;
                Console.WriteLine(y);
            }
            int z = x2 ?? 10; //使用null联合操作符
            Console.WriteLine(z);
        }
    }
}

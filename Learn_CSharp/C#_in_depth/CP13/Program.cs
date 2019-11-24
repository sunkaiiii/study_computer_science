using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace CP13
{
    class Program
    {
        //声明包含可选参数的方法并调用
        static void Dump(int x, int y=20, int z=30)
        {
            Console.WriteLine("x={0} y={1} z={2}", x, y, z);
        }

        //使用空默认值来处理非常量的情况
        static void AppendTimestamp(string filename,
            string message,
            Encoding encoding=null,
            DateTime? timestamp=null)
        {
            Encoding realEncoding = encoding ?? Encoding.UTF8;
            DateTime realTimestap = timestamp ?? DateTime.Now;
            //在这里使用命名实参
            using(TextWriter writer=new StreamWriter(path:filename,append:true,encoding:realEncoding))
            {
                writer.WriteLine("{0:s}: {1}", realTimestap, message);
            }
        }

        //记录参数求值
        static int Log(int value)
        {
            Console.WriteLine("Log: {0}", value);
            return value;
        }
        static void Main(string[] args)
        {
            Dump(1, 2, 3);
            Dump(1, 2);
            Dump(1);

            AppendTimestamp("utf8.txt", "First message");
            AppendTimestamp("ascii.txt", "ASCII", Encoding.ASCII);
            AppendTimestamp("utf8.txt", "Message in the future", null, new DateTime(2030, 1, 1));

            Dump(x: Log(1), y: Log(2), z: Log(3));
            Dump(z: Log(3), x: Log(1), y: Log(2));
            //滥用实参求值顺序
            int i = 0;
            Dump(x: ++i, y: ++i, z: ++i);
            i = 0;
            Dump(z: ++i, x: ++i, y: ++i);

            //用简单的类型来演示逆变性和协变性
            Converter<object, string> converter = x => x.ToString();
            Converter<string, string> contravariance = converter; //逆变性
            Converter<object, object> covariance = converter; //协变性
            Converter<string, object> both = converter; //双向

            Func<string> stringFunc = () => "";
            Func<object> objectFunc = () => new object();
            Func<object> combined = objectFunc + stringFunc; //多播委托与可变性不能混用，代码可以编译，但是会抛出异常。
            Console.WriteLine(combined());
        }
    }
}

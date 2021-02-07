using System;
using System.IO;
using System.Text;

namespace Chapter21
{
    class Program
    {
        static void Main(string[] args)
        {
            Action<int> action = generation => Console.WriteLine("Generation: " + generation);
            GCNotification.GCDone += action;
            string a = "123";
            StringBuilder sb = new StringBuilder();
            sb.Append(a);
            sb.Append("21312");
            Console.WriteLine(sb.ToString());
            GC.Collect();

            //安全的删除文件
            byte[] bytesToWrites = { 1, 2, 3, 4, 5 };
            //在这里还可以用using语句进行完美的替代
            FileStream fs = new FileStream("temp.dat", FileMode.Create);
            try
            {
                fs.Write(bytesToWrites, 0, bytesToWrites.Length);
            }
            finally
            {
                fs.Dispose(); //一定要显示关闭文件
            }
            File.Delete("temp.dat");
        }
    }
}

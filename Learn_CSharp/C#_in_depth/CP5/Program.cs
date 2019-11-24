using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace CP5
{
    class Program
    {
        delegate Stream StreamFactory();
        static MemoryStream GenerateSampleData()
        {
            byte[] buffer = new byte[16];
            for(int i=0;i<buffer.Length;i++)
            {
                buffer[i] = (byte)i;
            }
            return new MemoryStream(buffer);
        }

        //用匿名方法简便的排序文件
        static void SortAndShowFiles(string title,Comparison<FileInfo> sortOrder)
        {
            FileInfo[] files = new DirectoryInfo(@"C:\").GetFiles();
            Array.Sort(files, sortOrder);
            Console.WriteLine(title);
            foreach(FileInfo file in files)
            {
                Console.WriteLine("{0} ({1} bytes)", file.Name, file.Length);
            }
        }

        //不同种类的变量和匿名方法的关系
        static void EnclosingMethod()
        {
            int outerVariable = 5;
            string capturedVariable = "captured";
            if(DateTime.Now.Hour==23)
            {
                int normalLocalVarialble = DateTime.Now.Minute;
                Console.WriteLine(normalLocalVarialble);
            }
            Action x = delegate ()
             {
                 string anonLocal = "local to anonymous method";
                 Console.WriteLine(capturedVariable + anonLocal); //匿名方法捕获外部变量
            };
            x();
        }

        //捕捉变量的生存期延长了
        static Action CreateDelegateInstance()
        {
            int counter = 5;
            Action ret = delegate
              {
                  Console.WriteLine(counter++);
              };
            ret();
            return ret;
        }

        static void Main(string[] args)
        {
            StreamFactory factory = GenerateSampleData; //协变性来转换方法组
            using(Stream stream = factory()) //调用委托来获得stream
            {
                int data;
                while((data=stream.ReadByte())!=-1)
                {
                    Console.WriteLine(data);
                }
            }
            Action<string> printReverse = delegate (string text)
            {
                char[] chars = text.ToCharArray();
                Array.Reverse(chars);
                Console.WriteLine(new string(chars));
            };

            Action<int> printRoot = delegate (int number)
            {
                Console.WriteLine(Math.Sqrt(number));
            };

            Action<IList<double>> printMean = delegate (IList<double> numbers)
            {
                double total = 0;
                foreach (double value in numbers)
                {
                    total += value;
                }
                Console.WriteLine(total / numbers.Count);
            };

            printReverse("Hello World");
            printRoot(2);
            printMean(new double[] { 1.5, 2.5, 3, 4.5 });

            List<int> x = new List<int>();
            x.Add(5);
            x.Add(10);
            x.Add(15);
            x.Add(20);
            x.Add(25);
            x.ForEach(delegate (int n) { Console.WriteLine(Math.Sqrt(n)); }) ;

            //具有返回值的匿名方法
            Predicate<int> isEven = delegate (int xx) { return xx % 2 == 0; };
            Console.WriteLine(isEven(1));
            Console.WriteLine(isEven(4));

            SortAndShowFiles("Sorted by name: ", delegate (FileInfo f1, FileInfo f2)
             { return f1.Name.CompareTo(f2.Name); });
            SortAndShowFiles("Sorted by length:", delegate (FileInfo f1, FileInfo f2)
             { return f1.Length.CompareTo(f2.Length); });

            EnclosingMethod();

            //从匿名方法外访问一个变量
            string captured = "before x is created";
            Action ax = delegate
              {
                  Console.WriteLine(captured);
                  captured = "change by x";
              };
            captured = "directly before x is invoked";
            ax();
            Console.WriteLine(captured);
            captured = "before second invocation";
            ax();

            ax = CreateDelegateInstance();
            ax();
            ax();

            //使用多个委托来捕捉多个变量实例
            List<Action> list = new List<Action>();
            for(int index=0;index<5;index++)
            {
                int counter = index * 10;
                list.Add(delegate
                {
                    Console.WriteLine(counter); //打印并捕获变量
                    counter++;
                });
            }

            foreach(var t in list)
            {
                t(); //执行全部5个委托实例
            }

            list[0](); //第1个委托执行3次
            list[0]();
            list[0]();
            list[1]();  //第二个委托执行1次

            //捕捉不同作用域中的变量。
            //如有绝对必要的理由，不要使用这种玩法
            Action[] delegates = new Action[2];
            int outside = 0; //实例化一次
            for(int i=0;i<2;i++)
            {
                int inside = 0; //实例化多次
                delegates[i] = delegate
                  {
                      Console.WriteLine("({0},{1})", outside, inside);
                      outside++;
                      inside++;
                  };
            }

            var first = delegates[0];
            var last = delegates[1];

            first();
            first();
            first();
            last();
            last();
        }
    }
}

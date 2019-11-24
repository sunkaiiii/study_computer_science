using System;
using System.Linq;
using System.Threading;

namespace CP6
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] testInts = new int[] {1, 2, 3, 4, 5, 6, 7 };
            InterationSample sample = new InterationSample(testInts.Cast<object>().ToArray(), 0);
            foreach(var singleInt in sample)
            {
                Console.WriteLine(singleInt.ToString());
            }

            //执行显示迭代器及其调用者之间的序列
            //这段代码和foreach 的作用其实是接近的
            var iterable = InterationSample.CreateEnumerable();
            var iterator = iterable.GetEnumerator();
            Console.WriteLine("Starting to iterate");
            while(true)
            {
                Console.WriteLine("Calling MoveNext()...");
                bool result = iterator.MoveNext();
                Console.WriteLine("...MoveNext result={0}", result);
                if(!result)
                {
                    break;
                }
                Console.WriteLine("Fetching Current....");
                Console.WriteLine("...Current result={0}", iterator.Current);
            }

            //测试使用yield break
            var stop = DateTime.Now.AddSeconds(2);
            foreach(int i in InterationSample.CountWithTimeLimit(stop))
            {
                Console.WriteLine("Received{0}", i);
                Thread.Sleep(300);
            }

            //测试在迭代中终止迭代
            stop = DateTime.Now.AddSeconds(2);
            foreach (int i in InterationSample.CountWithTimeLimit(stop))
            {
                Console.WriteLine("Received {0}", i);
                if(i>3)
                {
                    Console.WriteLine("Returnning");
                    break; //此处return会触发迭代器的finally代码块hi行。
                    //因为foreach循环会在结束后调用Dispose方法，当dispose方法调用的时候，状态机会执行在代码当前暂停的范围内的任何finally方法。
                }
                Thread.Sleep(300);
            }

            //使用迭代器循环遍历文件中的行
            foreach(string line in InterationSample.ReadLines(@"C:\Users\sunkai\Documents\GitHub\study_computer_science\Learn_CSharp\CP6\Program.cs"))
            {
                Console.WriteLine(line);
            }

            //假装在使用LINQ
            var lines = InterationSample.ReadLines(@"C:\Users\sunkai\Documents\GitHub\study_computer_science\Learn_CSharp\CP6\Program.cs");
            Predicate<string> predicate = delegate (string line) { return line.StartsWith("using"); };
            foreach(string line in InterationSample.Where(lines,predicate))
            {
                Console.WriteLine(line);
            }
        }
    }
}

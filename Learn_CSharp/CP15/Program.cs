using System;
using System.Threading;
using System.Threading.Tasks;

namespace CP15
{
    class Program
    {
        static void PrintPageLength()
        {
            Task<int> lengthTask = AsyncTask.GetPageLengthAsync("http://csharpindepth.com");
            Console.WriteLine(lengthTask.Result);
        }
        static void Main(string[] args)
        {
            new AsyncTask().DisplayWebSite();
            Thread.Sleep(1000); //等待异步消息
            Console.WriteLine("now get the length...");
            var task = AsyncTask.MainAsync();
            PrintPageLength();
            task.Wait();

            //任务的取消
            Task t2 = AsyncTask.ThrowCancellationException();
            Console.WriteLine(task.Status);
            Console.WriteLine(t2.Status);

            //取消的延迟操作来取消异步方法
            var source = new CancellationTokenSource();
            var t3 = AsyncTask.DelayFor30Seconds(source.Token);
            source.CancelAfter(TimeSpan.FromSeconds(1));
            Console.WriteLine("Initial satus: {0}", t3.Status);
            try
            {
                t3.Wait();
            }
            catch(AggregateException e)
            {
                Console.WriteLine("Caught {0}", e.InnerExceptions[0]);
            }
            Console.WriteLine("Final Status: {0}", t3.Status);

            //创建异步匿名函数
            Func<Task> lambda = async () => await Task.Delay(1000);
            Func<Task<int>> anonMethod = async delegate ()
             {
                 Console.WriteLine("Started");
                 await Task.Delay(1000);
                 Console.WriteLine("Finished");
                 return 10;
             };
            Console.WriteLine("start lambda...");
            lambda();
            Console.WriteLine("start anonMethod...");
            var b = anonMethod();
            Console.WriteLine(b.Result);

            //使用lambda表达式创建并调用一个异步函数
            Func<int, Task<int>> function = async x =>
               {
                   Console.WriteLine("Starting... x={0}", x);
                   await Task.Delay(x * 1000);
                   Console.WriteLine("Finished... x={0}", x);
                   return x * 2;
               };
            Task<int> first = function(5);
            Task<int> second = function(3);
            Console.WriteLine("First result: {0}", first.Result);
            Console.WriteLine("Second result: {0}", second.Result);

            Console.WriteLine("get total length");
            Console.WriteLine(AsyncTask.ShowPageLengthsAsync("https://www.baidu.com", "https://www.google.com", "https://www.ithome.com").Result);
        }
    }
}

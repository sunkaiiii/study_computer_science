using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace concurrency_in_CSharp
{
    class Program
    {
        async Task DoSomeThingAsync()
        {
            int val = 13;
            //异步方式等待1秒
            await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
            val *= 2;
            //异步方式等待一秒
            await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
            Trace.WriteLine(val.ToString());
        }

        async Task WaitAsync()
        {
            //这里await会捕获当前上下文
            await Task.Delay(TimeSpan.FromSeconds(1));
            //这里会试图用上面捕获的上下文继续执行。
        }

        void DeadLock()
        {
            Task task = WaitAsync();
            //执行同步程序块，正在等待异步方法完成
            task.Wait();
            //如果UI或者ASP.NET的上下文调用这个代码，就会发生死锁
            //因为两种上下文每次只能运行一个线程。
            WaitAsync().ConfigureAwait(false); //解决方法
        }

        //一种实现数据并行的方法
        void CountNumbers(IEnumerable<int> numbers)
        {
            Parallel.ForEach(numbers, number => number.ToString());
        }

        IEnumerable<bool> PrimalityTest(IEnumerable<int> values)
        {
            return values.AsParallel().Select(val => val % 2 == 0);
        }

        //Parallel类的Fork/Join来实现任务并行
        void ProcessArray(double[] array)
        {
            Parallel.Invoke(() => ProcessPartialArray(array, 0, array.Length / 2),
                () => ProcessPartialArray(array, array.Length / 2, array.Length));
        }

        private void ProcessPartialArray(double[] array, int v1, int v2)
        {
            //
        }

        void ExceptionHandle()
        {
            //由于操作是并行执行的，多个一长就会同时发生
            //系统会把这些异常封装在AggregateException里.
            try
            {
                Parallel.Invoke(() => throw new Exception(),
                    () => throw new Exception());
            }catch(AggregateException ex)
            {
                ex.Handle(exception =>
                {
                    Trace.WriteLine(exception);
                    return true; //已经处理
                });
            }
        }

        void TPL()
        {
            try
            {
                var multiplyBlock = new TransformBlock<int, int>(item =>
                   {
                       if (item == 1)
                           throw new InvalidOperationException("Blech.");
                       return item * 2;
                   });
                var subtractBlock = new TransformBlock<int, int>(item => item - 2);
                multiplyBlock.LinkTo(subtractBlock, new DataflowLinkOptions { PropagateCompletion = true });
                multiplyBlock.Post(1);
                subtractBlock.Completion.Wait();
            }catch(AggregateException exception)
            {
                AggregateException ex = exception.Flatten();
                Trace.WriteLine(ex.InnerException);
            }
        }

        static void Main(string[] args)
        {
            var task = new Program().DoSomeThingAsync();
            Thread.Sleep(TimeSpan.FromSeconds(3));
        }
    }
}

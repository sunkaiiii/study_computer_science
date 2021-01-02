using System;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter2
{
    class Program
    {
        async Task<T> DelayResult<T>(T result, TimeSpan delay)
        {
            await Task.Delay(delay);
            return result;
        }

        //指数规避策略的一种实现
        async Task<string> DownloadStringWithRetries(HttpClient client, string uri)
        {
            TimeSpan nextDelay = TimeSpan.FromSeconds(1);
            for (int i = 0; i != 3; i++)
            {
                try
                {
                    return await client.GetStringAsync(uri);
                }
                catch { }
                await Task.Delay(nextDelay);
                nextDelay = nextDelay + nextDelay;
            }
            return await client.GetStringAsync(uri);
        }

        //Task Delay还可以用作简单的超时
        async Task<string> DownloadStringWithTimeout(HttpClient client, string uri)
        {
            using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(3));
            Task<string> downloadTask = client.GetStringAsync(uri);
            Task timeoutTask = Task.Delay(Timeout.InfiniteTimeSpan, cts.Token);
            Task completedTask = await Task.WhenAny(downloadTask, timeoutTask);
            if (completedTask == timeoutTask)
                return null;
            return await downloadTask;
        }

        interface IMyAsyncInterface
        {
            Task<int> GetValueAsync();
            Task DoSomethingAsync();
        }

        //需要通过异步签名实现同步方法
        class MySynchronousImplementation : IMyAsyncInterface
        {
            // 对于无返回值的方法，可以使用Task.CompletedTask
            public Task DoSomethingAsync()
            {
                return Task.CompletedTask;
            }

            public Task<T> GetErrorTask<T>()
            {
                return Task.FromException<T>(new NotImplementedException());
            }

            public Task<int> GetValueAsync()
            {
                return Task.FromResult(13);
            }

            //类似地，已经从给定的CancellationToken 中取消的任务，可以用Task.FromCanceled 创建
            Task<int> GetValueAsync(CancellationToken cancellation)
            {
                if (cancellation.IsCancellationRequested)
                    return Task.FromCanceled<int>(cancellation);
                return Task.FromResult(13);
            }
        }

        //报告进度
        async Task MyMethodAsync(IProgress<double> progress = null)
        {
            bool done = false;
            double percentComplete = 0;
            while(!done)
            {
                percentComplete += 10;
                progress?.Report(percentComplete);
                if(percentComplete >= 100)
                {
                    done = true;
                }
                await Task.Delay(TimeSpan.FromMilliseconds(300));
            }
        }

        //报告进度
        async Task CallMyMethodAsyncWithProgress()
        {
            var progress = new Progress<double>();
            progress.ProgressChanged += (sender, args) =>
            {
                Console.WriteLine(args);
            };
            await MyMethodAsync(progress);
        }


        //Task.whenAll处理异常
        async Task ThrowNotImplementedExceptionAsync()
        {
            throw new NotImplementedException();
        }
        async Task ThrowInvalidOperationExceptionAsync()
        {
            throw new InvalidOperationException();
        }

        async Task ObserveOneExceptionAsync()
        {
            var t1 = ThrowNotImplementedExceptionAsync();
            var t2 = ThrowInvalidOperationExceptionAsync();
            try
            {
                await Task.WhenAll(t1, t2);
            }catch (Exception ex) 
            {
                //// ex不是NotImplementedException就是InvalidOperationException
                Console.WriteLine(ex.GetType());
            }
        }

        async Task ObserveAllExceptionsAsync()
        {
            var t1 = ThrowNotImplementedExceptionAsync();
            var t2 = ThrowInvalidOperationExceptionAsync();
            Task allTaks = Task.WhenAll(t1, t2);
            try
            {
                await allTaks;
            }catch
            {
                AggregateException allExceptions = allTaks.Exception;
                Console.WriteLine(allExceptions);
            }
        }

        //在任务完成时处理他们
        async Task AwaitAndProcessAsync(Task<int> task)
        {
            int result = await task;
            Console.WriteLine(result);
        }

        async Task ProcessTasksAsync()
        {
            var t1 = DelayResult(2, TimeSpan.FromSeconds(2));
            var t2 = DelayResult(3, TimeSpan.FromSeconds(3));
            var t3 = DelayResult(1, TimeSpan.FromSeconds(1));
            var tasks = new[] { t1, t2, t3 };
            var tasksQuery = from t in tasks select AwaitAndProcessAsync(t);
            var processingTasks = tasksQuery.ToArray();
            await Task.WhenAll(processingTasks);
        }

        static void Main(string[] args)
        {
            var client = new HttpClient();
            var downloadProgram = new Program();
            var d1 = downloadProgram.DownloadStringWithRetries(client, "https://www.ithome.com/");
            var d2 = downloadProgram.DownloadStringWithTimeout(client, "https://www.notebookcheck.net/PWM-Ranking-Notebooks-Smartphones-and-Tablets-with-PWM.163979.0.html");
            Task progress = downloadProgram.CallMyMethodAsyncWithProgress();
            Task exceptionsOne = downloadProgram.ObserveOneExceptionAsync();
            Task exceptionsAll = downloadProgram.ObserveAllExceptionsAsync();
            Task handleAllProcess = downloadProgram.ProcessTasksAsync();
            foreach (var s in Task.WhenAll(d1, d2).Result)
            {
                if(s==null)
                {
                    Console.WriteLine("Task has been canceled");
                }
                Console.WriteLine(s);
            }
            progress.Wait();
            Task.WhenAll(exceptionsOne, exceptionsAll,handleAllProcess).Wait();
        }
    }
}

using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Linq;
using System.Collections.Generic;

namespace CP2
{
    class Program
    {
        //指数避退
        static async Task<string> DownloadStringWithRetries(string url)
        {
            using(var client=new HttpClient())
            {
                var nextDelay = TimeSpan.FromSeconds(1);
                for(int i=0;i!=3;i++)
                {
                    try
                    {
                        return await client.GetStringAsync(url);
                    }
                    catch { }
                    await Task.Delay(nextDelay);
                    nextDelay = nextDelay + nextDelay;
                }
                return await client.GetStringAsync(url); //最后重试，并不捕获异常

            }
        }

        //Task Delay所提供的超时功能
        static async Task<String> DownloadSttringWithTimeout(string url)
        {
            using (var client = new HttpClient())
            {
                var downloadTask = client.GetStringAsync(url);
                var timeoutTask = Task.Delay(3000);
                var completedTask = await Task.WhenAny(downloadTask, timeoutTask);
                if (completedTask == timeoutTask)
                    return null;
                return await downloadTask;
            }
        }

        //返回完成的任务
        //具有异步签名的同步方法
        interface IMyAsyncInterface
        {
            Task<int> GetValueAsync();
        }
        class MySynchronousImplementation:IMyAsyncInterface
        {
            public Task<int> GetValueAsync()
            {
                return Task.FromResult(13);
            }
        }

        //报告进度
        static async Task MyMethodAsync(IProgress<int> progress=null)
        {
            int percentComplete = 0;
            for(;percentComplete<100;percentComplete++)
            {
                if(progress!=null)
                {
                    progress.Report(percentComplete);
                }
            }
        }
        static async Task CallMyMethodAsync()
        {
            var progess = new Progress<int>();
            progess.ProgressChanged += (sender, args) =>
              {
                  Console.WriteLine(args);
              };
            await MyMethodAsync(progess);
        }

        //等待一组任务完成
        static async Task<int[]> WhenAllAsync()
        {
            var task1 = Task.FromResult(3);
            var task2 = Task.FromResult(5);
            var task3 = Task.FromResult(7);
            return await Task.WhenAll(task1, task2, task3);
        }

        //使用WhenAll进行下载
        static async Task<string> DownloadAllAsync(IEnumerable<string> urls)
        {
            var httpClient = new HttpClient();
            //定义每一个url的使用方法
            var downloads = urls.Select(url => httpClient.GetStringAsync(url));
            //同步开始所有的下载
            Task<string>[] downloadTasks = downloads.ToArray();
            //所有的下载就已经开始了
            string[] htmlPages = await Task.WhenAll(downloadTasks);
            return string.Concat(htmlPages);
        }

        //使用WhenAny判断第一个相应的URL的数据长度
        static async Task<int> FirstRespondingUrlAsync(IEnumerable<string> urls)
        {
            var httpClient = new HttpClient();
            var downloads = urls.Select(url => httpClient.GetByteArrayAsync(url));
            //同步开始所有的下载
            Task<byte[]>[] downloadTasks = downloads.ToArray();
            //等待任意一个任务完成
            Task<byte[]> completedTask = await Task.WhenAny(downloads);
            byte[] data = await completedTask;
            return data.Length;
        }

        //任务完成时的处理
        static async Task<int> DelayAndReturnAsync(int val)
        {
            await Task.Delay(TimeSpan.FromSeconds(val));
            return val;
        }

        static async Task AwaitAndProcessAsync(Task<int> task)
        {
            var result = await task;
            Console.WriteLine(result);
        }

        //现在，方法输出1，2，3
        static async Task ProcessTaskAsync()
        {
            var taskA = DelayAndReturnAsync(2);
            var taskB = DelayAndReturnAsync(3);
            var taskC = DelayAndReturnAsync(1);
            var tasks = new[] { taskA, taskB, taskC };
            var processingTasks = (from t in tasks select AwaitAndProcessAsync(t)).ToArray();
            await Task.WhenAll(processingTasks);
        }

        static void Main(string[] args)
        {
            var urls = new string[]
            {
                "https://sunkai.xyz:5001/api/NewsList/1",
                "https://sunkai.xyz:5001/api/NewsList/2",
                "https://sunkai.xyz:5001/api/NewsList/3",
                "https://sunkai.xyz:5001/api/NewsList/4",
                "https://sunkai.xyz:5001/api/NewsList/5"
            };
            Console.WriteLine(DownloadAllAsync(urls.ToList()).Result);

            Console.WriteLine(FirstRespondingUrlAsync(urls).Result);

            ProcessTaskAsync().Wait();
        }
    }
}

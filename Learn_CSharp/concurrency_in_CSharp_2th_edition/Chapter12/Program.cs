using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter12
{
    class Program
    {
        public class MyLockClass
        {
            //锁
            private readonly object _mutex = new object();
            private int _value;

            //异步锁
            private readonly SemaphoreSlim _semaphore = new SemaphoreSlim(1);
            private int _value2;
            public void Increment()
            {
                lock(_mutex)
                {
                    _value = _value + 1;
                }
            }

            public async Task DelayAndIncrementAsync()
            {
                await _semaphore.WaitAsync();
                try
                {
                    int oldValue = _value2;
                    await Task.Delay(TimeSpan.FromSeconds(oldValue));
                    _value2 = oldValue + 1;
                }finally
                {
                    _semaphore.Release();
                }
            }

            // 发送异步代码可以通过SemaphoreSlim进行节流
            async Task<string[]> DownloadUrlAsync(HttpClient client, IEnumerable<string> urls)
            {
                using var semaphore = new SemaphoreSlim(10);
                Task<string>[] tasks = urls.Select(async url =>
                {
                    await semaphore.WaitAsync(); //节流
                    try
                    {
                        return await client.GetStringAsync(url);
                    }
                    finally
                    {
                        semaphore.Release();
                    }
                }).ToArray();
                return await Task.WhenAll(tasks);
            }
        }

        class ResetEventClass
        {
            //阻塞信号
            private readonly ManualResetEventSlim _initialised = new ManualResetEventSlim();

            private int _value;
            
            public int WaitForInitialisation()
            {
                _initialised.Wait();
                return _value;
            }

            public void InitialiseFromAnotherThread()
            {
                _value = 13;
                _initialised.Set();
            }
        }

        // 异步信号
        class TaskCompletionClass
        {
            private readonly TaskCompletionSource<object> _initlised = new TaskCompletionSource<object>();

            private int _value1;
            private int _value2;

            public async Task<int> WaitForInialisationAsync()
            {
                await _initlised.Task;
                return _value1 + _value2;
            }

            public void Initialise()
            {
                _value1 = 13;
                _value2 = 17;
                _initlised.TrySetResult(null);
            }

            
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

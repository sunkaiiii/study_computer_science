using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace CP11
{
    class Program
    {
        //异步数据没有保护的情况
        class SharedData
        {
            public int Value { get; set; }
        }
        async Task ModifyValueAsync(SharedData data)
        {
            await Task.Delay(TimeSpan.FromSeconds(1));
            data.Value = data.Value + 1;
        }
        //没有同步的部分
        async Task<int> ModifyValueConcurrentlyAsync()
        {
            var data = new SharedData();
            var task1 = ModifyValueAsync(data);
            var task2 = ModifyValueAsync(data);
            var task3 = ModifyValueAsync(data);
            await Task.WhenAll(task1, task2, task3);
            return data.Value;
        }

        //下面一个代码，简单的并行修改同一个数据
        async Task<int> SimpleParalelismAsync()
        {
            int val = 0; //即使是既不变量，他可能也需要同步
            var task1 = Task.Run(() => { val++; });
            var task2 = Task.Run(() => { val++; });
            var task3 = Task.Run(() => { val++; });
            await Task.WhenAll(task1, task2, task3);
            return val;
        }

        //坏代码
        int ParallelSum(IEnumerable<int> values)
        {
            int result = 0;
            //最后一步的累加，没有同步
            Parallel.ForEach(source: values, localInit: () => 0, body: (item, state, localValue) => localValue + item, localFinally: localValue => { result += localValue; });
            return result;
        }

        //使用不可变集合时需要同步的情况
        async Task<bool> PlayWithStackAsync()
        {
            var stack = ImmutableStack<int>.Empty;

            var task1 = Task.Run(() => { stack = stack.Push(3); });
            var task2 = Task.Run(() => { stack = stack.Push(5); });
            var task3 = Task.Run(() => { stack = stack.Push(7); });

            await Task.WhenAll(task1, task2, task3);
            return stack.IsEmpty;
        }

        //使用阻塞锁
        class MyClassLock
        {
            //这个锁会保护_value
            private readonly object _mutex = new object();
            private int _value;
            public void Increment()
            {
                lock(_mutex)
                {
                    _value++;
                }
            }
        }
        
        //异步锁
        class MyClassSemaphore
        {
            //这个锁保护_value
            private readonly SemaphoreSlim _mutex = new SemaphoreSlim(1);
            private int _value;
            public int getValue()
            {
                return _value;
            }

            public async Task DelayAndIncrementAsync()
            {
                await _mutex.WaitAsync();
                try
                {
                    var oldValue = _value;
                    await Task.Delay(TimeSpan.FromSeconds(oldValue));
                    _value = oldValue + 1;
                }
                finally
                {
                    _mutex.Release();
                }
            }
        }

        //使用阻塞信号
        class MyClassManualResetEvent
        {
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

        //发送异步信号
        //有点go语言channel的那个 味儿了
        class MyClassSignal
        {
            private readonly TaskCompletionSource<object> _initialised = new TaskCompletionSource<object>();

            private int _value1;
            private int _value2;

            public async Task<int> WaitForinitialsationAsync()
            {
                await _initialised.Task;
                return _value1 + _value2;
            }

            public void Initialise()
            {
                _value1 = 13;
                _value2 = 17;
                _initialised.TrySetResult(null);
            }
        }

        //下面的代码是限流的相关
        //数据流的限流
        IPropagatorBlock<int,int> DataflowMultiplyBy2()
        {
            var options = new ExecutionDataflowBlockOptions
            {
                MaxDegreeOfParallelism = 10
            };
            return new TransformBlock<int,int>(data=>data*2, options);
        }
        //PLINQ的限流
        IEnumerable<int> ParallelMultiplyBy2(IEnumerable<int> values)
        {
            return values.AsParallel().WithDegreeOfParallelism(10).Select(item => item * 2);
        }

        //使用Paralel类
        void ParallelCalculate(IEnumerable<int> values)
        {
            var options = new ParallelOptions
            {
                MaxDegreeOfParallelism = 10
            };
            Parallel.ForEach(values, options, data => data *= 2);
        }

        //并发性异步代码可以用SemaphoreSlim来限流
        async Task<string[]> DownloadUrlsAsync(IEnumerable<string> urls)
        {
            var httpClient = new HttpClient();
            var semaphore = new SemaphoreSlim(10); //最高设置为0
            var tasks = urls.Select(async url =>
              {
                  await semaphore.WaitAsync();
                  try
                  {
                      return await httpClient.GetStringAsync(url);
                  }
                  finally
                  {
                      semaphore.Release();
                  }
              }).ToArray();
            return await Task.WhenAll(tasks);
        }

        static void Main(string[] args)
        {
            //本应该输出3，但实际可能不是
            Console.WriteLine(new Program().ModifyValueConcurrentlyAsync().Result);
            //本应该输出3，但实际可能不是
            Console.WriteLine(new Program().SimpleParalelismAsync().Result);
            var sepahoreClss = new MyClassSemaphore();
            sepahoreClss.DelayAndIncrementAsync().Wait();
            sepahoreClss.DelayAndIncrementAsync().Wait();
            Console.WriteLine(sepahoreClss.getValue());
            var classSignal = new MyClassSignal(); 
            Console.WriteLine("class signal has been created");
            Task.Run(async () =>
            {
                await Task.Delay(TimeSpan.FromSeconds(2));
                classSignal.Initialise();
            });
            Console.WriteLine(classSignal.WaitForinitialsationAsync().Result);
        }
    }
}

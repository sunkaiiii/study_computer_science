using Microsoft.VisualStudio.Threading;
using System;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace CP10
{
    class Program
    {
        //下面的代码定义了一个包含异步方法（不用async）的接口，对该接口的实现（用async），还定义了一个独立的方法，来调用该接口的方法
        interface IMyAsyncInterface
        {
            Task<int> CountBytesAsync(string url);
        }

        class MyAsyncClass : IMyAsyncInterface
        {
            public async Task<int> CountBytesAsync(string url)
            {
                var client = new HttpClient();
                var bytes = await client.GetByteArrayAsync(url);
                return bytes.Length;
            }
        }
        static async Task UseMyInterfaceAsync(IMyAsyncInterface service)
        {
            var result = await service.CountBytesAsync("https://www.baidu.com");
            Console.WriteLine(result);
        }

        //下面这段代码展示了异步工厂代码的方法模式
        class MyAsyncClassFactory
        {
            private MyAsyncClassFactory() { }

            private async Task<MyAsyncClassFactory> InitialiseAsync()
            {
                await Task.Delay(TimeSpan.FromSeconds(1));
                return this;
            }

            public static Task<MyAsyncClassFactory> createAsync()
            {
                var result = new MyAsyncClassFactory();
                return result.InitialiseAsync();
            }
        }

        //异步初始化，非使用工厂模式
        public interface IAsyncInitialisation
        {
            Task Initialisation { get; }
        }
        class MyFundamentalType: IAsyncInitialisation
        {
            public MyFundamentalType()
            {
                Initialisation = InitialiseAsync();
            }
            public Task Initialisation { get; private set; }

            private async  Task InitialiseAsync()
            {
                await Task.Delay(TimeSpan.FromSeconds(1));
            }
        }

        //使用异步的Lazy对象实现异步属性
        class AsyncProperty
        {
            public AsyncLazy<int> Data
            {
                get { return _data; }
            }
            private readonly AsyncLazy<int> _data = new AsyncLazy<int>(async () =>
              {
                  await Task.Delay(TimeSpan.FromSeconds(1));
                  return 13;
              });
        }

        //取消异步
        class MyClass:IDisposable
        {
            private readonly CancellationTokenSource _disposeCts = new CancellationTokenSource();

            public async Task<int> CalculateValueAsync()
            {
                //使用dispose的基本模式
                await Task.Delay(TimeSpan.FromSeconds(2), _disposeCts.Token);
                return 13;
            }
            public async Task<int> CalculateValueAsync(CancellationToken cancellation)
            {
                //实际应该在多一些检查
                //检查对象有没有被销毁
                using (var combinedCts = CancellationTokenSource.CreateLinkedTokenSource(cancellation, _disposeCts.Token))
                {
                    await Task.Delay(TimeSpan.FromSeconds(2), combinedCts.Token);
                    return 13;
                }

            }
            public void Dispose() //当取消的时候，会执行Dispose方法，随即执行Cancel
            {
                _disposeCts.Cancel();
            }

            async Task Test()
            {
                Task<int> task;
                using (var resourse = new MyClass())
                {
                    task = resourse.CalculateValueAsync();
                }
                //抛出异常
                var result = await task;
            }
        }

        //异步完成取消
        interface IAsyncCompletion
        {
            void Complete();
            Task Completion { get; }
        }
        class MyClassCompletion:IAsyncCompletion
        {
            private readonly TaskCompletionSource<object> _completion = new TaskCompletionSource<object>();
            private Task _completing;
            public Task Completion
            {
                get { return _completion.Task; }
            }

            public void Complete()
            {
                if (_completing != null)
                    return;
                _completing = CompleteAsync();
            }

            private async Task CompleteAsync()
            {
                try
                {
                    //一部等待任何运行中的操作
                }catch(Exception ex)
                {
                    _completion.TrySetException(ex);
                }
                finally
                {
                    _completion.TrySetResult(null);
                }
            }
        }
        static void Main(string[] args)
        {
            UseMyInterfaceAsync(new MyAsyncClass()).Wait();
            var factory= MyAsyncClassFactory.createAsync().Result;
            Console.WriteLine(factory);
            var funType = new MyFundamentalType();
            funType.Initialisation.Wait();
            Console.WriteLine(funType);
            var data = new AsyncProperty().Data.GetValue();
            Console.WriteLine(data);
        }
    }
}

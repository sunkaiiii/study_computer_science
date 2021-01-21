using Nito.AsyncEx;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter11
{
    class Program
    {
        //异步构造工厂
        // 不过，这种方法并不能用于某些场景，比如在以来代码注入的时候。没有任何主流的依赖注入或控制库的反转可以用于async代码
        class MyAsyncClass
        {
            //异步属性
            public AsyncLazy<int> Data
            {
                get { return _data; }
            }

            private readonly AsyncLazy<int> _data = new AsyncLazy<int>(async () =>
            {
                await Task.Delay(TimeSpan.FromSeconds(1));
                return 13;
            });

            private MyAsyncClass()
            {

            }

            private async Task<MyAsyncClass> InitialiseAsync()
            {
                await Task.Delay(TimeSpan.FromDays(1));
                return this;
            }

            public static Task<MyAsyncClass> CreateAsync()
            {
                var result = new MyAsyncClass();
                return result.InitialiseAsync();
            }
        }

        // 以取消来代表丢弃
        class MyDisposeClass : IDisposable
        {
            private readonly CancellationTokenSource _disposeCts = new CancellationTokenSource();
            public async Task<int> CalculateValueAsync()
            {
                await Task.Delay(TimeSpan.FromSeconds(2), _disposeCts.Token);
                return 13;
            }

            public void Dispose()
            {
                _disposeCts.Cancel();
            }
        }

        // 异步丢弃是C# 8.0和.NET Core 3.0引入的技术
        class MyDisposeAsyncClass :IAsyncDisposable
        {
            public async ValueTask DisposeAsync()
            {
                await Task.Delay(TimeSpan.FromSeconds(2));
            }

        }

        // 使用异步丢弃
        async Task UsingAsyncDisposable()
        {
            await using(var myClass = new MyDisposeAsyncClass())
            {
                
            }
        }

        static void Main(string[] args)
        {
           
            
        }
    }
}

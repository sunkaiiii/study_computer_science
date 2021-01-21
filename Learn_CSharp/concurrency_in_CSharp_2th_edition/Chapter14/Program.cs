using System;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter14
{
    class Program
    {
        //使用Lazy初始化贡献资源
        static int _simpleValue;
        static readonly Lazy<int> MySharedInteger = new Lazy<int>(() => _simpleValue++);
        //异步版本的初始化
        static readonly Lazy<Task<int>> MyAsyncSharedInteger = new Lazy<Task<int>>(async () =>
        {
            await Task.Delay(TimeSpan.FromSeconds(2)).ConfigureAwait(false);
            return _simpleValue++;
        });
        //只会初始化一次
        void UseSharedInteger()
        {
            int sharedValue = MySharedInteger.Value;
        }

        async Task UseSharedIntegerAsync()
        {
            await MyAsyncSharedInteger.Value;
            await MyAsyncSharedInteger.Value;
            await MyAsyncSharedInteger.Value;
            await MyAsyncSharedInteger.Value;
            await MyAsyncSharedInteger.Value;
        }

        // System.Reactive延迟计算
        void SubscibeWithDefer()
        {
            var invokeServerObservable = Observable.Defer(() => GetValueAsync().ToObservable());
            invokeServerObservable.Subscribe(_ => { });
            invokeServerObservable.Subscribe(_ => { });
        }
        async Task<int> GetValueAsync()
        {
            Console.WriteLine("Calling server...");
            await Task.Delay(TimeSpan.FromSeconds(2));
            Console.WriteLine("Returning result...");
            return 13;
        }


        // 使用AsyncLocal来实现隐式状态
        private static AsyncLocal<Guid> _operationId = new AsyncLocal<Guid>();
        async Task DoLongOperationAsync()
        {
            _operationId.Value = Guid.NewGuid();
            await DoSomeStepOfOperationAsync();
        }
        async Task DoSomeStepOfOperationAsync()
        {
            await Task.Delay(100);
            Console.WriteLine("In operation: " + _operationId.Value);
        }

        //节流进度更新
        //第一个版本，会疯狂地更新
        string Solve(IProgress<int> progress)
        {
            var endTime = DateTime.UtcNow.AddSeconds(3);
            int value = 0;
            while(DateTime.UtcNow<endTime)
            {
                value++;
                progress?.Report(value);
            }
            return value.ToString();
        }
        //节流版本的进度更新
        public static class ObservableProgress
        {
            private sealed class EventProgress<T>:IProgress<T>
            {
                void IProgress<T>.Report(T value) => OnReport?.Invoke(value);
                public event Action<T> OnReport;
            }

            public static (IObservable<T>, IProgress<T>) Create<T>()
            {
                var progress = new EventProgress<T>();
                var observable = Observable.FromEvent<T>(
                    handler => progress.OnReport += handler,
                    handler => progress.OnReport -= handler);
                return (observable, progress);
            }

            public static (IObservable<T>,IProgress<T>) CreateForUI<T>(TimeSpan? sampleInterval = null)
            {
                var (observable, progress) = Create<T>();
                observable = observable.Sample(sampleInterval ?? TimeSpan.FromMilliseconds(100)).ObserveOn(SynchronizationContext.Current); //应用节流
                return (observable, progress);
            }
        }



        static void Main(string[] args)
        {
            var program = new Program();
            program.UseSharedInteger();
            program.UseSharedInteger();
            program.UseSharedInteger();
            program.UseSharedInteger();
            program.UseSharedInteger();
            Console.WriteLine(_simpleValue);
            program.UseSharedIntegerAsync().Wait();
        }
    }
}

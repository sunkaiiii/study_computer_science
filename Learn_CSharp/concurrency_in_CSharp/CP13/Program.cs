using System;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;
using System.Threading.Tasks;

namespace CP13
{
    class Program
    {
        //使用Lazy来进行初始化
        static int _simpleValue;
        static readonly Lazy<int> MySharedInteger = new Lazy<int>(() => _simpleValue++);
        //如果初始化过程中需要执行异步任务，可以采用一个非常类似的方法
        static readonly Lazy<Task<int>> MySharedAsyncInteger = new Lazy<Task<int>>(async () =>
          {
              await Task.Delay(TimeSpan.FromSeconds(2)).ConfigureAwait(false);
              return _simpleValue++;
          });
        int UseSharedInteger()
        {
            //使用Lazy类
            //不管有多少个线程调用这个类，工厂委托都只会运行一次。
            int sharedValue = MySharedInteger.Value;
            return sharedValue;
        }
        async Task<int> GetSharedIntegerAsync()
        {
            int sharedValue = await MySharedAsyncInteger.Value;
            return sharedValue;
        }


        static async Task<int> GetValueAsync()
        {
            Console.WriteLine("Calling server...");
            await Task.Delay(TimeSpan.FromSeconds(2));
            Console.WriteLine("Return result...");
            return 13;
        }
        static void Main(string[] args)
        {
            var program= new Program();
            var task = program.GetSharedIntegerAsync();
            int value = program.UseSharedInteger();
            Console.WriteLine(value);
            Console.WriteLine(task.Result);

            //Rx延迟求值
            var invokeServerObservable = Observable.Defer(() => GetValueAsync().ToObservable());
            invokeServerObservable.Subscribe(_=>{ });
            invokeServerObservable.Subscribe(_ => { });
            Console.ReadKey();
        }
    }
}

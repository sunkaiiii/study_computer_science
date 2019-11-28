using Microsoft.Reactive.Testing;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Net.Http;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Threading.Tasks;

namespace CP6
{
    class Program
    {
        //测试Rx
        public interface IHttpService
        {
            IObservable<string> GetString(string url);
        }

        //被测试的类，它消耗一个Observable对象依赖项，生成一个Observable对象作为输出
        public class MyTimeoutClass
        {
            private readonly IHttpService _httpService;
            public MyTimeoutClass(IHttpService httpService)
            {
                _httpService = httpService;
            }
            public IObservable<string> GetStringWithTimeout(string url, IScheduler scheduler=null) //为了让observable便于测试，就要允许它调用它的指定的程序调度器
            {
                return _httpService.GetString(url).Timeout(TimeSpan.FromSeconds(1),scheduler??Scheduler.Default);
            }

            class SuccessHttpServiceStub:IHttpService
            {
                //加入调度功能，然后加入一个可变的延迟
                public IScheduler Scheduler { get; set; }
                public TimeSpan Delay { get; set; }
                //Return操作符创建一个只有一个元素的冷序列，用来构建简答的存根。
                public IObservable<string> GetString(string url)
                {
                    return Observable.Return("stub").Delay(Delay,Scheduler);
                }
            }
            
            //Throw操作符返回一个错误结束的Observable对象。
            private class FailureHttpServiceStub:IHttpService
            {
                public IObservable<string> GetString(string url)
                {
                    return Observable.Throw<string>(new HttpRequestException());
                }
            }

            //用TestScheduler可以对时间进行完整的控制，但通常只需要写好代码然后调用TestScheduler.Start。
            //在整个测试进行的过程中，Start方法可以用虚拟的方式推进时间
            [TestMethod]
            public async Task MyTimeoutClass_SuccessfulGet_ReturnsResult()
            {
                var scheduler = new TestScheduler();
                var stub = new SuccessHttpServiceStub
                {
                    Scheduler = scheduler,
                    Delay = TimeSpan.FromSeconds(0.5),
                };
                var my = new MyTimeoutClass(stub);
                //SingleAsync可用来做简单的单元测试，它返回一个Task<T>对象，该对象在下一个事件到达时完成
                // var result = await my.GetStringWithTimeout("http://kworb.net/pop/").SingleAsync();
                string result = null;
                my.GetStringWithTimeout("http://kworb.net/pop/", scheduler).Subscribe(r => { result = r; });
                scheduler.Start();
                Assert.AreEqual("stub", result);
            }

            [TestMethod]
            public async Task MyTimeoutClass_FailedGet_PropagatesFailure()
            {
                //var stub = new FailureHttpServiceStub();
                //var my = new MyTimeoutClass(stub);
                //await ThrowsExceptionAsync<HttpRequestException>(async () =>
                //{
                //    await my.GetStringWithTimeout("http://kworb.net/pop/").SingleAsync();
                //});

                //使用调度器，测试超时的情况就很容易了
                var scheduler = new TestScheduler();
                var stub = new SuccessHttpServiceStub
                {
                    Scheduler = scheduler,
                    Delay = TimeSpan.FromSeconds(1.5),
                };
                Exception result = null;
                var my = new MyTimeoutClass(stub);
                my.GetStringWithTimeout("http://kworb.net/pop/",scheduler).Subscribe(_ => Assert.Fail("Received value"), ex => { result = ex; });
                scheduler.Start();
                Assert.IsInstanceOfType(result, typeof(TimeoutException));
            }
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

using System;
using System.Net;
using System.Net.Http;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;

namespace CP5
{
    class Program
    {
        //使用ObserveOn来把通知给一个指定的上下文
        private static void ObserveOn()
        {
            //如果不用ObserveOn，他切换时候的Thread ID可能是不同的
            Console.WriteLine("UI thread is " + Environment.CurrentManagedThreadId);
            Observable.Interval(TimeSpan.FromSeconds(1)).Subscribe(x => Console.WriteLine("Interval " + x + " on thread " + Environment.CurrentManagedThreadId));
            //使用了ObserveOn，就是相同的
            var uiContext = SynchronizationContext.Current;
            if(uiContext!=null)
            {
                Observable.Interval(TimeSpan.FromSeconds(1)).ObserveOn(Scheduler.CurrentThread).Subscribe(x => Console.WriteLine("Interval " + x + " on thread " + Environment.CurrentManagedThreadId));

                //还可以通过ObserveOn转移当前线程。
                Observable.Interval(TimeSpan.FromMilliseconds(100)).ObserveOn(Scheduler.Default)
                    .Select(x =>
                    {
                        //此处是异步的，在别的线程计算的
                        x++;
                        //一些复杂的计算
                        return x;
                    }).ObserveOn(uiContext)
                    .Subscribe(x => Console.WriteLine(x)); //切回到UI线程
            }
        }

        private static void BufferAndWindow()
        {
            //每两个做一次缓冲
            Observable.Interval(TimeSpan.FromSeconds(1)).Buffer(2).Subscribe(x => Console.WriteLine(DateTime.Now.Second + " : Got " + x[0] + " and " + x[1]));

            //创建一个事件组，每组包含两个事件
            Observable.Interval(TimeSpan.FromSeconds(1)).Window(2)
                .Subscribe(group =>
                {
                    Console.WriteLine(DateTime.Now.Second + ": starting new group");
                    //每次传递，但是分组为两个一组
                    group.Subscribe(
                        x => Console.WriteLine(DateTime.Now.Second + ": Saw " + x),
                        () => Console.WriteLine(DateTime.Now.Second + ": Ending group"));
                });
        }

        private static void ThrottleAndSample()
        {
            //使用Throttle来将窗口期内到达的最后一个事件发布出去
            //如果一直有事件，它会重新计时
            //所以这个一直都不会输出x
            Observable.Interval(TimeSpan.FromMilliseconds(100))
                .Throttle(TimeSpan.FromSeconds(1))
                .Subscribe(x => Console.WriteLine(x));

            //Sample注册时间段
            //发布每个时间段内的最后一个注册的事件
            Observable.Interval(TimeSpan.FromMilliseconds(100))
                .Sample(TimeSpan.FromSeconds(1))
                .Subscribe(x => Console.WriteLine("Sample: " + x));
        }

        private static void TimeOut()
        {
            //Timeout操作符设定一个超时时间
            //如果超时，则产生OnError
            var client = new HttpClient();
            client.GetAsync("http://kworb.net/pop/").ToObservable()
                .Timeout(TimeSpan.FromSeconds(1)).Subscribe( //如果设置为4左右，不会超时
                x => Console.WriteLine(DateTime.Now.Second + ": No Timeout " + x.ToString())
                ,ex=>Console.WriteLine(ex));

            //如果超时，事件流就结束了
            //TImeout有重载，可以用另外一个流来处理超时的问题。
            //var item2 = Observable.FromEventPattern<int,int>(handler=>to be implement) .Select(x => x);
           // client.GetAsync("sfasfsaf").ToObservable().Timeout(TimeSpan.FromSeconds(1), item2); //当然这个item2是毫无意义的
        }

        static void Main(string[] args)
        {
            //使用Rx
            //使用FromEventPattern封装事件
            var process = new Progress<int>();
            var progressReports = Observable.FromEventPattern<int>(
                handler => process.ProgressChanged += handler,
                handler => process.ProgressChanged += handler
                );
            progressReports.Subscribe(data => Console.WriteLine("OnNext: "+data.EventArgs));

            ObserveOn();
            BufferAndWindow();
            ThrottleAndSample();
            TimeOut();
            Thread.Sleep(TimeSpan.FromSeconds(10));
        }
    }
}

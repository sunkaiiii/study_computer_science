using System;
using System.Net.Http;
using System.Reactive;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;

namespace Chapter6
{
    class Program
    {

        void ConvertEvent()
        {
            var progree = new Progress<int>();
            IObservable<EventPattern<int>> progressReports = Observable.FromEventPattern<int>(
                handler => progree.ProgressChanged += handler,
                handler => progree.ProgressChanged -= handler);
            progressReports.Subscribe(data => Console.WriteLine("OnNext: " + data.EventArgs));

            // 对于比较老的委托，对timer的包装
            var timer = new System.Timers.Timer(interval: 1000) { Enabled = true };
            IObservable<EventPattern<ElapsedEventArgs>> ticks = Observable.FromEventPattern<ElapsedEventHandler, ElapsedEventArgs>(
                handler => (s, a) => handler(s, a),
                handler => timer.Elapsed += handler,
                handler => timer.Elapsed -= handler);
            ticks.Subscribe(data => Console.WriteLine("OnNext: " + data.EventArgs.SignalTime));
        }

        // 缓冲事件数据
        void BufferEvent()
        {
            Observable.Interval(TimeSpan.FromSeconds(1)).Buffer(2).Subscribe(x=>Console.WriteLine($"{DateTime.Now.Second}: Got {x[0]} and {x[1]}"));
        }

        // 使用Window来创建两两一对的事件分组
        void GroupEvent()
        {
            Observable.Interval(TimeSpan.FromSeconds(1))
                .Window(2)
                .Subscribe(group =>
                {
                    Console.WriteLine($"{DateTime.Now.Second}: Starting new group");
                    group.Subscribe(
                        x => Console.WriteLine($"{DateTime.Now.Second}: Saw {x}"),
                        () => Console.WriteLine($"{DateTime.Now.Second}: Ending group"));
                });
        }

        void SwitchContext()
        {
            // SynchronizationContext uiContext = SynchronizationContext.Current; //传递UI线程的上下文
            Console.WriteLine($"UI thread is {Environment.CurrentManagedThreadId}");
            Observable.Interval(TimeSpan.FromSeconds(1)).ObserveOn(Scheduler.Default).Subscribe(x => Console.WriteLine($"Interval {x} on thread {Environment.CurrentManagedThreadId}")); //使用Scheduler.Defaut让此方法离开UI线程。每一次Time interval事件都会触发
        }

        //节流
        void Throttle()
        {
            var timer = new System.Timers.Timer(interval: 1000) { Enabled = true };
            var ticks = Observable.FromEventPattern<ElapsedEventHandler, ElapsedEventArgs>(
                handler => (s, a) => handler(s, a),
                handler => timer.Elapsed += handler,
                handler => timer.Elapsed -= handler).Select(x=>x.EventArgs.SignalTime)
                .Throttle(TimeSpan.FromSeconds(1))
                .Subscribe(x => Console.WriteLine(
                $"{DateTime.Now.Second}: Saw {x}"));
        }

        void Sample()
        {
            var timer = new System.Timers.Timer(interval: 1000) { Enabled = true };
            var ticks = Observable.FromEventPattern<ElapsedEventHandler, ElapsedEventArgs>(
               handler => (s, a) => handler(s, a),
               handler => timer.Elapsed += handler,
               handler => timer.Elapsed -= handler).Select(x => x.EventArgs.SignalTime)
               .Sample(TimeSpan.FromSeconds(1))
               .Subscribe(x => Console.WriteLine(x));
        }

        void GetWithTimeout(HttpClient client)
        {
            client.GetStringAsync("http://www.ithome.com").ToObservable().Timeout(TimeSpan.FromSeconds(3))
                .Subscribe(
                x => Console.WriteLine($"{DateTime.Now.Second}: Saw {x.Length}"), 
                ex => Console.WriteLine(ex));
        }

        static void Main(string[] args)
        {
            var p = new Program();
            p.SwitchContext();
            p.BufferEvent();
            p.GroupEvent();
            p.GetWithTimeout(new HttpClient());
            Task.Delay(10000).Wait();
        }
    }
}

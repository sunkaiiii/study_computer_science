using System;
using System.Collections.Generic;
using System.Linq;
using System.Reactive.Linq;
using System.Threading.Tasks.Dataflow;

namespace Chapter8
{
    class Program
    {
        static void Main(string[] args)
        {
            // 考虑把数据流块用作可观察流的输入
            var buffer = new BufferBlock<int>();
            IObservable<int> integers = buffer.AsObservable();
            integers.Subscribe(data => Console.WriteLine(data), ex => Console.WriteLine(ex), () => Console.WriteLine("done"));
            buffer.Post(13);
            buffer.Complete();
            buffer.Completion.Wait();

            // 考虑使用数据流网络并把它当作可观察流的终点
            IObservable<DateTimeOffset> ticks = Observable.Interval(TimeSpan.FromSeconds(1))
                .Timestamp()
                .Select(x => x.Timestamp)
                .Take(5);
            var display = new ActionBlock<DateTimeOffset>(x => Console.WriteLine(x));
            ticks.Subscribe(display.AsObserver());
            try
            {
                display.Completion.Wait();
                Console.WriteLine("Done");
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex);
            }
        }
    }
}

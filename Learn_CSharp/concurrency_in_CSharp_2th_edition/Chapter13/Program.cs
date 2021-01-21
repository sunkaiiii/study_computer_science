using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace Chapter13
{
    class Program
    {
        // 调度并行代码
        void CalculateInts(IEnumerable<int> collections)
        {
            var scuedulerPair = new ConcurrentExclusiveSchedulerPair(TaskScheduler.Default, maxConcurrencyLevel: 8);
            TaskScheduler scheduler = scuedulerPair.ConcurrentScheduler;
            ParallelOptions options = new ParallelOptions { TaskScheduler = scheduler };
            Parallel.ForEach(collections, options, i => i++);
        }

        void ScheduleTPL()
        {
            var options = new ExecutionDataflowBlockOptions
            {
                TaskScheduler = TaskScheduler.FromCurrentSynchronizationContext()
            };
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var displayBlock = new ActionBlock<int>(result => Console.WriteLine(result));
            multiplyBlock.LinkTo(displayBlock);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

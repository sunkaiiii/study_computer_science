using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace CP12
{
    class Program
    {
        //使用调度器控制并行代码
        void CalculateValues(IEnumerable<int> collections)
        {
            var schedulerPair = new ConcurrentExclusiveSchedulerPair(TaskScheduler.Default, maxConcurrencyLevel: 8);
            TaskScheduler scheduler = schedulerPair.ConcurrentScheduler; //限制自身并发的对象，这时通常不需要使用ExclusiveScheduler
            ParallelOptions options = new ParallelOptions { TaskScheduler = scheduler };
            Parallel.ForEach(collections, options, data => data++);
        }

        //用调度器实现数据流的同步
        void TaskDataFlow()
        {
            var options = new ExecutionDataflowBlockOptions
            {
                TaskScheduler = TaskScheduler.FromCurrentSynchronizationContext()
            };
            var mutiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var displayBlock = new ActionBlock<int>(result => Console.WriteLine(result));
            mutiplyBlock.LinkTo(displayBlock);

        }
        static void Main(string[] args)
        {
            //使用Task.Run而将任务调度到线程池
            Task task = Task.Run(() =>
            {
                Thread.Sleep(TimeSpan.FromSeconds(2));
            });
            //Task同样也可以用异步表达式
            Task<int> task2 = Task.Run(async () =>
              {
                  await Task.Delay(TimeSpan.FromSeconds(1));
                  return 13;
              });
        }
    }
}

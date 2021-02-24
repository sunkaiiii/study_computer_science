using System;
using System.Threading;

namespace Chapter26
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Main thread: starting a dedicated thread " + "tod do an asynchronous operation");
            Thread dedicatedThread = new Thread(ComputeBoundOp);
            dedicatedThread.Start(5);

            Console.WriteLine("Main thread: Doing other work here");
            Thread.Sleep(10000);

            dedicatedThread.Join();



            var t = new Thread(Worker);
            t.IsBackground = true; //使线程成为后台线程
            t.Start();
            Console.WriteLine("Return from Main");
        }

        private static void ComputeBoundOp(object state)
        {
            Console.WriteLine("In ComputeBoundOp: state={0} ", state);
            Thread.Sleep(1000); //模拟做其他任务
        }

        private static void Worker()
        {
            Thread.Sleep(10000);
            //下面这行代码只有在前提线程执行时才会显示
        }
    }
}

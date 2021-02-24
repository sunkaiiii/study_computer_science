using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter27
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Main thread: queuing an asynchronous operation");
            ThreadPool.QueueUserWorkItem(ComputeBoundOp, 5);
            Console.WriteLine("Main thread: Doing other work here...");
            Thread.Sleep(2000);

            //取消任务
            CancellationTokenSource cts = new CancellationTokenSource();
            ThreadPool.QueueUserWorkItem(o => Count(cts.Token, 1000));
            cts.Cancel();
            Thread.Sleep(2000);

            //使用任务工厂
            Task parent = new Task(() =>
            {
                var cts = new CancellationTokenSource();
                var tf = new TaskFactory<double>(cts.Token, TaskCreationOptions.AttachedToParent, TaskContinuationOptions.ExecuteSynchronously, TaskScheduler.Default);
                var childTaskss = new[]
                {
                    tf.StartNew(()=>Math.Sqrt(10000)),
                    tf.StartNew(()=>Math.Sqrt(2000)),
                    tf.StartNew(()=>Math.Sqrt(int.MaxValue))
                };

                //任何子任务抛出异常，就取消其余子任务
                for (int i = 0; i < childTaskss.Length; i++)
                {
                    childTaskss[i].ContinueWith(t => cts.Cancel(), TaskContinuationOptions.OnlyOnFaulted);
                }

                tf.ContinueWhenAll(childTaskss, completedTasks => completedTasks.Where(t => !t.IsFaulted && !t.IsCanceled).Max(t => t.Result), CancellationToken.None)
                .ContinueWith(t => Console.WriteLine("The maximum is: " + t.Result), TaskContinuationOptions.ExecuteSynchronously);
            });

            parent.ContinueWith(p =>
            {
                StringBuilder sb = new StringBuilder("The following exception(s) occurred: " + Environment.NewLine);

                //显示未处理的异常
                foreach (var e in p.Exception.Flatten().InnerExceptions)
                {
                    sb.AppendLine(" " + e.GetType().ToString());
                    Console.WriteLine(sb.ToString());
                }
            }, TaskContinuationOptions.OnlyOnFaulted);
            parent.Start();
            var size = DirectoryBytes(@"D:\Onedrive\图片\Camera Roll", "", SearchOption.AllDirectories);
            Console.WriteLine("The directory size is: "+size);
            parent.Wait();
        }

        private static void ComputeBoundOp(object state)
        {
            Console.WriteLine("In ComputeBoundOp: state={0} ", state);
            Thread.Sleep(1000); //模拟做其他任务
        }

        private static void Count(CancellationToken token, int countTo)
        {
            for (int i = 0; i < countTo; i++)
            {
                if (token.IsCancellationRequested)
                {
                    Console.WriteLine("Count is cancelled");
                    break;
                }
                Console.WriteLine(i);
                Thread.Sleep(200);
            }
        }

        //演示如何利用Parallel库进行目录中的所有文件长度的计算
        private static int DirectoryBytes(string path, string searchPattern, SearchOption searchOption)
        {
            var files = Directory.EnumerateFiles(path, searchPattern, searchOption);
            int masterTotal = 0;

            ParallelLoopResult result = Parallel.ForEach(files, () => 0
            , (file, loopState, index, taskLocalTotal) =>
            {
                int fileLength = 0;
                FileStream fs = null;
                try
                {
                    fs = File.OpenRead(file);
                    fileLength = (int)fs.Length;
                }
                catch { }
                finally
                {
                    if (fs != null)
                    {
                        fs.Dispose();
                    }
                }
                return taskLocalTotal + fileLength;
            }
            , taskLocalTotal =>
            {
                Interlocked.Add(ref masterTotal, taskLocalTotal);
            });
            return masterTotal;
        }
    }
}

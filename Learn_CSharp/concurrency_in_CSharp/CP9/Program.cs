using System;
using System.Threading;
using System.Threading.Tasks;

namespace CP9
{
    class Program
    {
        //取消请求
        void IssueCancelRequest()
        {
            var cts = new CancellationTokenSource();
            //var task = CancelableMethodAsync(cts.Token);
            //......
            //
            cts.Cancel(); //发送取消请求
        }

        //取消会面临的三种问题
        async Task IssueCancelRequestAsync()
        {
            var cts = new CancellationTokenSource();
            //var task = CancelableMethodAsync(cts.Token);
            //......
            //
            cts.Cancel();
            //一部等待才做结束
            try
            {
                //await task;
            }catch(OperationCanceledException)
            {
                //说明操作被取消
            }catch(Exception)
            {
                //说明在取消之前，操作出错
                throw;
            }
        }

        public int CancelableMethod(CancellationToken cancellation)
        {
            for(int i=0;i!=100;i++)
            {
                Thread.Sleep(10000); //假装再做一些计算工作
                cancellation.ThrowIfCancellationRequested();
            }
            return 42;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

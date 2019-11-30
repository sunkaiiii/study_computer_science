using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

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

        //构建超时后取消的任务
        async Task IssueTimeoutAsync()
        {
            var cts = new CancellationTokenSource(TimeSpan.FromSeconds(5));
            var token = cts.Token;
            await Task.Delay(TimeSpan.FromSeconds(10), token);
        }
        //另外一种超时的方案，如果已经有了一个CancellationTokenSource实例，则可以对该实例启动一个超时
        async Task IssueTimeoutAsync2()
        {
            var cts = new CancellationTokenSource();
            var token = cts.Token;
            cts.CancelAfter(TimeSpan.FromSeconds(5));
            await Task.Delay(TimeSpan.FromSeconds(10), token);
        }

        //支持取消的async
        public async Task<int> CancelableMethodAsync(CancellationToken cancellationToken)
        {
            await Task.Delay(TimeSpan.FromDays(2), cancellationToken);
            return 42;
        }

        //取消并行代码
        static void HandleInts(IEnumerable<int> ints, CancellationToken token)
        {
            Parallel.ForEach(ints, new ParallelOptions { CancellationToken = token }, i => Console.WriteLine(i));
        }

        //并行LINQ的取消
        static IEnumerable<int> MultiplyBy2(IEnumerable<int> values,CancellationToken token)
        {
            return values.AsParallel().WithCancellation(token).Select(item => iten * 2);
        }

        //取消数据流网络
        IPropagatorBlock<int,int> CreateMyCustomBlock(CancellationToken token)
        {
            var blockOptions = new ExecutionDataflowBlockOptions
            {
                CancellationToken = token
            };
            //将超时规则传递给每个任务
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2,blockOptions);
            var addBlock = new TransformBlock<int, int>(item => item + 2,blockOptions);
            var divideBlock = new TransformBlock<int, int>(item => item / 2, blockOptions);
            
            var flowCompletion = new DataflowLinkOptions
            {
                PropagateCompletion = true //让网格中的每一个任务都支持撤销
            };
            multiplyBlock.LinkTo(addBlock, flowCompletion);
            addBlock.LinkTo(divideBlock, flowCompletion);
            return DataflowBlock.Encapsulate(multiplyBlock, divideBlock);
        }

        //注入取消
        //使用连接的取消标记
        async Task<HttpResponseMessage> GetWithTimeoutAsync(String url, CancellationToken token)
        {
            var client = new HttpClient();
            //如果接收到取消，它会传递给httpclient，同时自己也会被取消
            using(var cts=CancellationTokenSource.CreateLinkedTokenSource(token))
            {
                cts.CancelAfter(TimeSpan.FromSeconds(2));
                var combinedToken = cts.Token;
                return await client.GetAsync(url, combinedToken);
            }
        }

        //与其他取消体系的互操作
        //使用CancellationToken.Register
        async Task<PingReply> PingAsync(string hostNameOrAddress, CancellationToken token)
        {
            var ping = new Ping();
            using(token.Register(()=>ping.SendAsyncCancel())) //这样，发出取消请求时回调函数就会使用SendAsyncCancel方法。
            {
                return await ping.SendPingAsync(hostNameOrAddress);
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

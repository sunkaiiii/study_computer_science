using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace Chapter10
{
    class Program
    {

        void IssueCancelRequest()
        {
            using var cts = new CancellationTokenSource();
            var task = Task.Delay(10, cts.Token);
            //发起取消请求
            cts.Cancel();
        }

        async Task IssueCancelRequestAsync()
        {
            using var cts = new CancellationTokenSource();
            var task = Task.Delay(10, cts.Token);
            cts.Cancel();
            try
            {
                await task;
            } catch (OperationCanceledException)
            {
                // 如果运行到了这里，那么操作尚未完成便已被取消
                Console.WriteLine("Cancel");
            } catch (Exception)
            {
                // 如果运行到了这里，那么在取消生效之前，操作已经以报错完成
                Console.WriteLine("Error");
            }
        }

        // 通过轮询来相应取消
        public int CancelableMethod(CancellationToken cancellationToken)
        {
            for (int i = 0; i < 100; i++)
            {
                Thread.Sleep(1000); //此处会有一些计算操作
                cancellationToken.ThrowIfCancellationRequested();
            }

            //如果循环很紧的话
            for (int i = 0; i < 100000; i++)
            {
                Thread.Sleep(1); //此处会有一部分计算操作
                if (i % 1000 == 0)
                    cancellationToken.ThrowIfCancellationRequested();
            }

            return 40;
        }

        // 因超时而取消
        async Task IssueTimeoutAsync()
        {
            using var cts = new CancellationTokenSource(TimeSpan.FromSeconds(5)); // 构建超时
            //cts.CancelAfter(TimeSpan.FromSeconds(4)); //另外一种构建超时的方法
            var token = cts.Token;
            await Task.Delay(TimeSpan.FromSeconds(10), token);
        }

        // 取消async代码
        public async Task<int> CancelableMethodAsync(CancellationToken token)
        {
            await Task.Delay(TimeSpan.FromSeconds(2), token);
            return await Task.FromResult(2);
        }

        // 取消System.Reactive
        async void CancelRx()
        {
            var cancellation = new CancellationTokenSource();
            await Observable.Range(0, 10).TakeLast(1).ToTask(cancellation.Token);
            //可以取消整个观察流
            await Observable.Range(0, 10).ToList().ToTask(cancellation.Token);
        }

        //取消并行代码
        ParallelQuery<int> CancelParallel(IEnumerable<int> ints,CancellationToken token)
        {
            Parallel.ForEach(ints, new ParallelOptions { CancellationToken = token }, number => number++);

            //PLINQ的取消
            return ints.AsParallel().WithCancellation(token).Select(number => number * 2);
        }

        // 取消数据流网格
        IPropagatorBlock<int,int> CreateMyCustomBlock(CancellationToken cancellation)
        {
            var blockOptions = new ExecutionDataflowBlockOptions
            {
                CancellationToken = cancellation
            };
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2, blockOptions);
            var addBlock = new TransformBlock<int, int>(item => item + 2, blockOptions);
            var divideBlock = new TransformBlock<int, int>(item => item / 2, blockOptions);
            var flowCompletion = new DataflowLinkOptions
            {
                PropagateCompletion = true
            };
            multiplyBlock.LinkTo(addBlock, flowCompletion);
            addBlock.LinkTo(divideBlock, flowCompletion);
            return DataflowBlock.Encapsulate(multiplyBlock, divideBlock);
        }

        // 注入取消请求
        async Task<HttpResponseMessage> GetWithTimeoutAsync(HttpClient client, string url, CancellationToken cancellation)
        {
            using var cts = CancellationTokenSource.CreateLinkedTokenSource(cancellation);
            cts.CancelAfter(TimeSpan.FromSeconds(2));
            var token = cts.Token; //关联取消
            return await client.GetAsync(url, token);
        }

        public class Ping
        {
            public void Cancel() { }
        }

        // 设置取消回调，来兼容老的api
        async Task<int> PingAsync(CancellationToken cancellation)
        {
            var ping= new Ping();
            // 这些回调会轮流保持Ping对象的生命，为了避免内存及资源的溢出，当不再需要回调时，必须丢弃回调注册
            using var _ = cancellation.Register(() => ping.Cancel()); //设置取消的回调
            return await Task.FromResult(1);
        }

        static void Main(string[] args)
        {
            new Program().IssueCancelRequestAsync().Wait();
            new Program().IssueTimeoutAsync().Wait();
        }
    }
}

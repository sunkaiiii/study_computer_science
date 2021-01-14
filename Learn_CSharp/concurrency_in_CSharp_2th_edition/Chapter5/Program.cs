using System;
using System.Threading.Tasks.Dataflow;

namespace Chapter5
{
    class Program
    {
        async void HandleException()
        {
            var block = new TransformBlock<int, int>(item =>
           {
               if (item == 1)
                   throw new InvalidOperationException("Blech.");
               return item * 2;
           });
            block.Post(1);
            block.Post(2);

            // 捕获异常
            try
            {
                block = new TransformBlock<int, int>(item =>
                {
                    if (item == 1)
                        throw new InvalidOperationException("Blech.");
                    return item * 2;
                });
                block.Post(1);
                await block.Completion;
            }catch(InvalidCastException)
            {
                //处理异常
            }
        }

        void DisposeLink()
        {
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var subtractBlock = new TransformBlock<int, int>(item => item - 2);

            IDisposable link = multiplyBlock.LinkTo(subtractBlock); //可以用来解耦

            multiplyBlock.Post(1);
            multiplyBlock.Post(2);

            //解耦数据流块
            link.Dispose();
        }

        // 块的节流
        void LoadBalance()
        {
            var sourceBlock = new BufferBlock<int>();
            var options = new DataflowBlockOptions { BoundedCapacity = 1 };
            var targetBlockA = new BufferBlock<int>(options);
            var targetBlockB = new BufferBlock<int>(options);
            sourceBlock.LinkTo(targetBlockA);
            sourceBlock.LinkTo(targetBlockB);
        }

        // 块的并行处理
        void ParallelHandling()
        {
            var multiplyBlock = new TransformBlock<int, int>(
                item => item * 2,
                new ExecutionDataflowBlockOptions
                {
                    MaxDegreeOfParallelism = DataflowBlockOptions.Unbounded //设置并行
                }); ;
            var subtrackBlock = new TransformBlock<int, int>(item => item - 2);
            multiplyBlock.LinkTo(subtrackBlock);
        }

        // 创建自定义块
        IPropagatorBlock<int, int> CustomBlock()
        {
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var addBlock = new TransformBlock<int, int>(item => item + 2);
            var divideBlock = new TransformBlock<int, int>(item => item / 2);

            var flowCompletion = new DataflowLinkOptions { PropagateCompletion = true };
            multiplyBlock.LinkTo(addBlock, flowCompletion);
            addBlock.LinkTo(divideBlock, flowCompletion);

            // 任意包含单个输入快和输出块的部分，都可以通过Encaosulate方法切出来
            return DataflowBlock.Encapsulate(multiplyBlock, divideBlock);
        }

        static void Main(string[] args)
        {
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var subtractBlock = new TransformBlock<int, int>(item => item * 2);

            var options = new DataflowLinkOptions { PropagateCompletion = true }; // 可以传播完成状态
            multiplyBlock.LinkTo(subtractBlock);

            // 第一个数据流块的完成状态会自动的传播到第2个数据流块
            multiplyBlock.Complete();
            subtractBlock.Completion.Wait();
        }
    }
}

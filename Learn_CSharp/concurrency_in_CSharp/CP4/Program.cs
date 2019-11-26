using System;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace CP4
{
    class Program
    {
        public static async Task TPL()
        {
            //TPL数据流link方法
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var subtractBlock = new TransformBlock<int, int>(item => item - 2);
            //建立连接后，从multiplyBlock出来的数据将进入subtractBlock
            multiplyBlock.LinkTo(subtractBlock);
            var options = new DataflowLinkOptions { PropagateCompletion = true };
            var divideBlock = new TransformBlock<int, double>(item => item / 2.0);
            subtractBlock.LinkTo(divideBlock, options);
            divideBlock.Complete();
            await divideBlock.Completion;

        }

        public static void TPLDispose()
        {
            var multipleBlock = new TransformBlock<int, int>(item => item * 2);
            var subtractBlock = new TransformBlock<int, int>(item => item - 2);
            IDisposable link = multipleBlock.LinkTo(subtractBlock);
            multipleBlock.Post(1);
            multipleBlock.Post(2);
            //段开始拒块的链接
            //数据可能已经通过链接传出去，也可能没有
            //在实际应用中，考虑使用代码块，而不是调用dispose
            link.Dispose();
        }

        public static void TPLBounded()
        {
            var sourceBLock = new BufferBlock<int>();
            var options = new DataflowBlockOptions { BoundedCapacity = 1 };
            var targetBlockA = new BufferBlock<int>(options);
            var targetBlockB = new BufferBlock<int>(options);
            sourceBLock.LinkTo(targetBlockA);
            sourceBLock.LinkTo(targetBlockB);
        }

        public static void MultipleTPL()
        {
            var multiplyBlock = new TransformBlock<int, int>( //允许任意数量的任务，来同时对数据进行倍增。
                item => item * 2,
                new ExecutionDataflowBlockOptions
                {
                    MaxDegreeOfParallelism = DataflowBlockOptions.Unbounded
                });
            var subtractBlock = new TransformBlock<int, int>(item => item - 2);
            multiplyBlock.LinkTo(subtractBlock);
        }

        //创建自定义数据流
        public static IPropagatorBlock<int,int> CreateMyCustomBlock()
        {
            var multiplyBlock = new TransformBlock<int, int>(item => item * 2);
            var addBlobck = new TransformBlock<int, int>(item => item + 2);
            var divideBlock = new TransformBlock<int, int>(item => item / 2);
            var flowCompletion = new DataflowLinkOptions { PropagateCompletion = true };
            multiplyBlock.LinkTo(addBlobck, flowCompletion);
            addBlobck.LinkTo(divideBlock, flowCompletion);
            return DataflowBlock.Encapsulate(multiplyBlock, divideBlock);
        }

        static void Main(string[] args)
        {
        
        }
    }
}

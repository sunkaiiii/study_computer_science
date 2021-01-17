using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Threading.Channels;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace Chapter9
{
    class Program
    {
        static async Task ReaderCode(ChannelReader<int>reader)
        {
            await foreach(int value in reader.ReadAllAsync())
            {
                Console.WriteLine(value);
            }
        }

        static async Task TPLReaderCode(BufferBlock<int> block)
        {
            while(await block.OutputAvailableAsync())
            {
                Console.WriteLine(await block.ReceiveAsync());
            }

            //如果有多个消费者的情况, 上面的就不适用了
            while(true)
            {
                int item;
                try
                {
                    item = await block.ReceiveAsync();
                }catch(InvalidOperationException)
                {
                    break;
                }
                Console.WriteLine(item);
            }
        }

        static async Task BlockAsyncQueue()
        {
            //异步的生产者代码
            ActionBlock<int> queue = new ActionBlock<int>(item => Console.WriteLine(item));
            await queue.SendAsync(7);
            await queue.SendAsync(13);

            //同步的生产者代码
            queue.Post(7);
            queue.Post(13);
            queue.Complete();
        }

        static void Main(string[] args)
        {
            // 不可变栈和队列
            ImmutableStack<int> stack = ImmutableStack<int>.Empty;
            stack = stack.Push(13);
            stack = stack.Push(7);
            foreach(int item in stack)
            {
                Console.WriteLine(item);
            }
            int lastItem;
            stack = stack.Pop(out lastItem);
            Console.WriteLine(lastItem);

            // 队列和栈类似
            ImmutableQueue<int> queue = ImmutableQueue<int>.Empty;
            queue = queue.Enqueue(13);
            queue = queue.Enqueue(7);
            // 在7之前显示13
            foreach (int item in queue)
                Console.WriteLine(item);
            int nextItem;
            queue = queue.Dequeue(out nextItem);
            // 只显示13
            Console.WriteLine(nextItem);


            //不可变列表
            ImmutableList<int> list = ImmutableList<int>.Empty;
            list = list.Insert(0, 13);
            list = list.Insert(0, 7);
            // 在13之前显示7
            foreach (int item in list)
                Console.WriteLine(item);
            list = list.RemoveAt(1);

            //不可变set
            //hash的
            ImmutableHashSet<int> hashSet = ImmutableHashSet<int>.Empty;
            hashSet = hashSet.Add(13);
            hashSet = hashSet.Add(7);
            // 以不可预知的顺序显示7和13
            foreach (int item in hashSet)
                Console.WriteLine(item);
            hashSet = hashSet.Remove(7);
            //sorted
            ImmutableSortedSet<int> sortedSet = ImmutableSortedSet<int>.Empty;
            sortedSet = sortedSet.Add(13);
            sortedSet = sortedSet.Add(7);
            // 在13之前显示7
            foreach (int item in sortedSet)
                Console.WriteLine(item);
            int smallestItem = sortedSet[0];
            // smallestItem == 7
            sortedSet = sortedSet.Remove(7);

            //不可变Dictionary
            //无排序
            ImmutableDictionary<int, string> dictionary =
            ImmutableDictionary<int, string>.Empty;
            dictionary = dictionary.Add(10, "Ten");
            dictionary = dictionary.Add(21, "Twenty-One");
            dictionary = dictionary.SetItem(10, "Diez");
            // 以不可预知的顺序显示10Diez和21Twenty-One
            foreach (KeyValuePair<int, string> item in dictionary)
                Console.WriteLine(item.Key + item.Value);
            string ten = dictionary[10];
            // ten == "Diez"
            dictionary = dictionary.Remove(21);
            //有排序
            ImmutableSortedDictionary<int, string> sortedDictionary =
            ImmutableSortedDictionary<int, string>.Empty;
            sortedDictionary = sortedDictionary.Add(10, "Ten");
            sortedDictionary = sortedDictionary.Add(21, "Twenty-One");
            sortedDictionary = sortedDictionary.SetItem(10, "Diez");
            // 在21Twenty-One之前显示10Diez
            foreach (KeyValuePair<int, string> item in sortedDictionary)
                Console.WriteLine(item.Key + item.Value);
            ten = sortedDictionary[10];
            // ten == "Diez"
            sortedDictionary = sortedDictionary.Remove(21);

            //线程安全的字典
            var cd = new ConcurrentDictionary<int, string>();
            string newvalue = cd.AddOrUpdate(0, key => "Zero", (key, oldvalue) => "Zero");
            bool keyExists = cd.TryGetValue(0, out string currentvalue);
            if(keyExists)
            {
                Console.WriteLine(currentvalue);
            }
            bool keyExisted = cd.TryRemove(0, out currentvalue);
            {
                Console.WriteLine(currentvalue);
            }

            //阻塞队列
            BlockingCollection<int> blockQueue = new BlockingCollection<int>();
            blockQueue.Add(7);
            blockQueue.Add(13);
            blockQueue.CompleteAdding(); //标记完成
            //消费者消费
            foreach(int item in blockQueue.GetConsumingEnumerable())
            {
                Console.WriteLine(item);
            }

            // 异步队列
            Channel<int> channelQueue = Channel.CreateUnbounded<int>();
            //生产者代码
            ChannelWriter<int> writer = channelQueue.Writer;
            var t = writer.WriteAsync(7);
            var t2 = writer.WriteAsync(13);
            writer.Complete();
            Task.WhenAll(t.AsTask(), t2.AsTask()).Wait();
            //消费者代码
            ChannelReader<int> reader = channelQueue.Reader;
            ReaderCode(reader).Wait();
            //使用TPL完成
            var asyncQueue = new BufferBlock<int>();
            //生产者代码
            var t3 = asyncQueue.SendAsync(7);
            var t4 = asyncQueue.SendAsync(13);
            asyncQueue.Complete();
            Task.WhenAll(t3, t4).Wait();
            //消费者代码
            TPLReaderCode(asyncQueue).Wait();


            //节流队列的几种创建方式
            Channel<int> cq = Channel.CreateBounded<int>(1);
            BufferBlock<int> b = new BufferBlock<int>(new DataflowBlockOptions { BoundedCapacity = 1 });
            BlockingCollection<int> bb = new BlockingCollection<int>(boundedCapacity: 1);

            //采样队列的几种创建方式
            cq = Channel.CreateBounded<int>(new BoundedChannelOptions(1) { FullMode = BoundedChannelFullMode.DropOldest});

            //使用ActionBlock来定义阻塞异步队列
            BlockAsyncQueue().Wait();

        }
    }
}

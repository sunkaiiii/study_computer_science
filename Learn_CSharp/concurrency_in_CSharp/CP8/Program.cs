using System;
using System.Collections.Concurrent;
using System.Collections.Immutable;
using System.Threading.Tasks.Dataflow;

namespace CP8
{
    class Program
    {
        static void Main(string[] args)
        {
            //不可变栈和队列
            var stack = ImmutableStack<int>.Empty;
            //使用方法和普通的栈接近
            //但是每次修改都需要返回一个新的集合
            stack = stack.Push(13); 
            stack=stack.Push(7);
            foreach (var item in stack)
                Console.WriteLine(item);
            int lastItem;
            stack = stack.Pop(out lastItem);
            //队列的使用方式类似
            var queue = ImmutableQueue<int>.Empty;
            queue = queue.Enqueue(13);
            queue = queue.Enqueue(7);
            foreach (var item in queue)
                Console.WriteLine(item);
            int nextItem;
            queue = queue.Dequeue(out nextItem);
            Console.WriteLine(nextItem);

            //不可变列表支持List<T>的方法
            var list = ImmutableList<int>.Empty;
            list = list.Insert(0, 13);
            list = list.Insert(0, 7);
            foreach (var item in list)
                Console.WriteLine(item);
            list = list.RemoveAt(1);

            //两种不可变Set集合类型
            var hashSet = ImmutableHashSet<int>.Empty;
            hashSet = hashSet.Add(13);
            hashSet = hashSet.Add(7);
            //显示7和13，顺序不固定
            foreach (var item in hashSet)
                Console.WriteLine(item);
            hashSet = hashSet.Remove(7);
            //另外一种Set
            var sortedSet = ImmutableSortedSet<int>.Empty;
            sortedSet = sortedSet.Add(13);
            sortedSet = sortedSet.Add(7);
            //显示7，13
            foreach (var item in sortedSet)
                Console.WriteLine(item);
            sortedSet = sortedSet.Remove(7);

            //不可变字典的使用方式也非常相似
            var dictionary = ImmutableDictionary<int, string>.Empty;
            dictionary = dictionary.Add(10, "Ten");
            dictionary = dictionary.Add(21, "Twenty-One");
            dictionary = dictionary.SetItem(10, "Diez");//注意setItem的用法
            //次序不固定
            foreach (var item in dictionary)
                Console.WriteLine(item.Key + item.Value);
            var ten = dictionary[10];
            dictionary = dictionary.Remove(21);
            var sortedDictionary = ImmutableSortedDictionary<int, string>.Empty;
            sortedDictionary = sortedDictionary.Add(10, "Ten");
            sortedDictionary = sortedDictionary.Add(21, "Twenty-One");
            sortedDictionary = sortedDictionary.SetItem(10, "Diez");
            foreach (var item in sortedDictionary)
                Console.WriteLine(item.Key + item.Value);
            var ten2 = sortedDictionary[10];
            sortedDictionary = sortedDictionary.Remove(21);




            //ConcurrentDictionary
            var concurrentDictionary = new ConcurrentDictionary<int, string>();
            var newValue = concurrentDictionary.AddOrUpdate(0, key => "Zero", (key, oldValue) => "Zero"); //写入一个数据
            //也可以使用直接索引法
            concurrentDictionary[0] = "Zero";
            string currentValue;
            bool keyExists = concurrentDictionary.TryGetValue(0, out currentValue); //尝试读取一个值
            string removedValue;
            bool keyExisted = concurrentDictionary.TryRemove(0, out removedValue);


            //生产者消费者
            BlockingCollection<int> _blockingQueue = new BlockingCollection<int>(boundedCapacity:1); //缓冲区为1的
            _blockingQueue.Add(1); //立即添加完成
            //_blockingQueue.Add(13); //阻塞直到上一个数字被消耗掉。
            _blockingQueue.CompleteAdding();


            //可以在创建的时候指明规则
            var _blockingStack = new BlockingCollection<int>(new ConcurrentStack<int>());
            var _blockingBag = new BlockingCollection<int>(new ConcurrentBag<int>());


            //异步队列
            BufferBlock<int> _asyncQueue = new BufferBlock<int>();
            _asyncQueue.SendAsync(7);
            _asyncQueue.SendAsync(13);
            _asyncQueue.Complete();

        }
    }
}

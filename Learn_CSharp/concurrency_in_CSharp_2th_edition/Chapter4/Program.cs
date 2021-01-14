using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter4
{
    class Program
    {
        //用Parallel库进行并行聚合
        int ParallelSum(IEnumerable<int> values)
        {
            object mutex = new object();
            int result = 0;
            Parallel.ForEach(values, localInit: () => 0, body: (item, state, localValue) => localValue + item, localFinally: localValue =>
            {
                lock (mutex)
                    result += localValue;
            });
            return result;
        }

        int ParallelSumPLINQ(IEnumerable<int> values)
        {
            return values.AsParallel().Sum();
        }

        int ParallelSumAggregate(IEnumerable<int> values)
        {
            return values.AsParallel().Aggregate(seed: 0, func: (sum, item) => sum + item);
        }

        class Node
        {
            public Node Left { get; set; }
            public Node Right { get; set; }
            public int value;
        }

        //动态并行处理
        void Traverse(Node current)
        {
            DoExpensiveActionOnNode(current);
            if (current.Left != null)
            {
                Task.Factory.StartNew(() => Traverse(current.Left), CancellationToken.None, TaskCreationOptions.AttachedToParent, TaskScheduler.Default);
            }
            if (current.Right != null)
            {
                Task.Factory.StartNew(() => Traverse(current.Right), CancellationToken.None, TaskCreationOptions.AttachedToParent, TaskScheduler.Default);
            }
        }

        void ProcessTree(Node root)
        {
            Task task = Task.Factory.StartNew(() => Traverse(root), CancellationToken.None, TaskCreationOptions.None, TaskScheduler.Default);
            task.Wait();
        }

        void DoExpensiveActionOnNode(Node node)
        {
            Task.Delay(600).Wait();
        }

        // 可以保证原始顺序
        IEnumerable<int> MultiplyBy(IEnumerable<int> values)
        {
            return values.AsParallel().AsOrdered().Select(values => values * 2);
        }

        IEnumerable<int> MultiplyBy2(IEnumerable<int> values)
        {
            return values.AsParallel().AsOrdered().Select(values => values * 2);
        }
        static void Main(string[] args)
        {
            var random = new Random();
            int i = 50000000;
            List<int> list = new List<int>();
            while (i-- > 0)
            {
                list.Add(random.Next(10));    
            }
            var program = new Program();
            Console.WriteLine(program.ParallelSum(list));
            Console.WriteLine(program.ParallelSumPLINQ(list));
            Console.WriteLine(program.ParallelSumAggregate(list));

            i = 500;
            Node node = new Node();
            Node root = node;
            while(i>0)
            {
                if(random.Next()%2==0)
                {
                    node.Left = new Node();
                    node = node.Left;
                }
                else
                {
                    node.Right = new Node();
                    node = node.Right;
                }
                i--;
            }
            program.ProcessTree(root);
        }
    }
}

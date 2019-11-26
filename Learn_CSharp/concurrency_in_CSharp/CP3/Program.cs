using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace CP3
{
    class Program
    {
        //并行聚合
        //这不是最高效的实现方式
        //适用锁来保护共享状态
        static int ParallelSum(IEnumerable<int> values)
        {
            object mutex = new object();
            int result = 0;
            Parallel.ForEach(source: values, localInit: () => 0, body: (item, state, localValue) => localValue + item, localFinally: localValue =>
            {
                lock (mutex)
                    result += localValue;
            });
            return result;

        }

        //并行LINQ对聚合的支持，比Parallel类更加顺手
        static int ParallelSumPLINQ(IEnumerable<int> values)
        {
            return values.AsParallel().Sum();
        }

        //使用PLINQ的Aggregate实现通用的聚合功能
        static int ParallelSumPLINQAggregate(IEnumerable<int> values)
        {
            return values.AsParallel().Aggregate(
                seed: 0,
                func: (sum, item) => sum + item);
        }


        //使用Parallel Invoke来实现并行调用方法
        static void ProcessArray(double[] array)
        {
            Parallel.Invoke(
                () => ProcessPartialArray(array, 0, array.Length / 2),
                () => ProcessPartialArray(array, array.Length / 2, array.Length));
        }
        static void ProcessPartialArray(double[] array,int begin,int end)
        {

        }

        //如果在运行之前无法确定调用的数量，可以在Parallel.Invode函数中输入一个委托数组
        static void DoAcrion20Times(Action action)
        {
            Action[] actions = Enumerable.Repeat(action, 20).ToArray();
            Parallel.Invoke(actions);
        }

        //使用TPL来实现动态的并行处理
        public class Node
        {
            public Node Left { get; set; }
            public Node Right { get; set; }
        }
        void Traverse(Node current)
        {
            //DoExpensiveActionOnNode(current); //假设这里有一个非常耗时的任务
            Action<Node> action = (Node node) => Task.Factory.StartNew(() => Traverse(node), CancellationToken.None, TaskCreationOptions.AttachedToParent, TaskScheduler.Default);
            if (current.Left != null)
            {
                action(current.Left);
            }
            if(current.Right!=null)
            {
                action(current.Right);
            }
        }
        public void ProcessTree(Node root)
        {
            var task = Task.Factory.StartNew(() => Traverse(root), CancellationToken.None, TaskCreationOptions.None, TaskScheduler.Default);
            task.Wait();
        }

        static void Main(string[] args)
        {
            var values1 = Enumerable.Range(0, 100000000);
            var values2 = Enumerable.Range(0, 100000000);
            var values3= Enumerable.Range(0, 100000000);
            Console.WriteLine("start calculate");
            Console.WriteLine(ParallelSum(values1));
            //Console.WriteLine(ParallelSumPLINQ(values2));
            Console.WriteLine(ParallelSumPLINQAggregate(values3));

            var value4 = Enumerable.Range(0, 10000000).Select(x => (double)x).ToArray();
            ProcessArray(value4);

            //TPL
            Node node = new Node();
            node.Left = new Node();
            node.Left.Left = new Node();
            node.Right = new Node();
            node.Left.Right = new Node();
            node.Right.Left = new Node();
            node.Right.Right = new Node();
            new Program().ProcessTree(node);
        }
    }
}

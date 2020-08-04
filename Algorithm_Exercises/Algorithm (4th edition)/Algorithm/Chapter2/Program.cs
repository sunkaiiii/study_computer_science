using System;
using Chapter1;
using StandardLibraries;

namespace Chapter2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Insertion, 20000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Selection, 20000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Shell, 2000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Merge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedMerge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.NonRecursiveMerge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Quick, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedQuick, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedThreeWayQuick, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Heap, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.System, 3000000, 3));
            //int M = StdIn.ReadInt();
            //MaxPQ<int> qp = new MaxPQ<int>(M + 1);
            //while (!StdIn.IsEmpty())
            //{
            //    qp.Insert(StdIn.ReadInt());
            //    if (qp.Size > M)
            //        qp.Delete();
            //}

            //Stack<int> stack = new Stack<int>();
            //while (!qp.IsEmpty)
            //    stack.Push(qp.Delete());
            //while (!stack.IsEmpty)
            //    StdOut.Println(stack.Pop());
        }
    }
}

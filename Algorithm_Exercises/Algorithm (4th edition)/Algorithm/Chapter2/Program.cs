using System;
using StandardLibraries;

namespace Chapter2
{
    class Program
    {
        static void Main(string[] args)
        {
            //Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Insertion, 30000, 3));
            //Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Selection, 30000, 3));
            //Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Shell, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Merge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedMerge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.NonRecursiveMerge, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Quick, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedQuick, 3000000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.ImprovedThreeWayQuick, 3000000, 3));
        }
    }
}

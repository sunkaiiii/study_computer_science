using System;
using StandardLibraries;

namespace Chapter2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Insertion, 30000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Selection, 30000, 3));
            Console.WriteLine(SortExample.TimeRandomInput(AlgorithmOptions.Shell, 30000, 3));
        }
    }
}

using Chapter5.StringSort;
using StandardLibraries;
using System;
using System.IO;

namespace Chapter5
{
    class Program
    {

        private static void LSDSort()
        {
            var fileName = "LSD.txt";
            var strings = ReadFile(fileName);
            PrintArray(strings);
            StdOut.Println("After sorting.....");
            LSD.Sort(ref strings, strings[0].Length);
            PrintArray(strings);
        }
        private static void MSDSort()
        {
            var fileName = "MSD.txt";
            var strings = ReadFile(fileName);
            PrintArray(strings);
            StdOut.Println("After sorting.....");
            MSD.Sort(strings);
            PrintArray(strings);
        }

        private static void Q3String()
        {
            var fileName = "3String.txt";
            var strings = ReadFile(fileName);
            PrintArray(strings);
            StdOut.Println("After sorting...");
            Quick3String.Sort(strings);
            PrintArray(strings);
        }

        private static string[] ReadFile(string fileName)
        {
            var scanner = new Scanner(new StreamReader(File.OpenRead(fileName)));
            var strings = scanner.ReadAllLines();
            return strings;
        }

        private static void PrintArray(string[] strings)
        {
            foreach (var s in strings)
            {
                StdOut.Println(s);
            }
        }

        static void Main(string[] args)
        {
            LSDSort();
            MSDSort();
            Q3String();
        }


    }
}

using System;
using System.IO;
using System.Text;
using StandardLibraries;

namespace Chapter6
{
    class Program
    {

        private static string[] ReadFile(string fileName)
        {
            var scanner = new Scanner(new StreamReader(File.OpenRead(fileName)));
            var strings = scanner.ReadAllLines();
            return strings;
        }

        static void Main(string[] args)
        {
            var texts = ReadFile("tale.txt");
            var sb = new StringBuilder();
            sb.Append(texts);
            var text = sb.ToString();
            var sa = new SuffixArray(text);
        }
    }
}

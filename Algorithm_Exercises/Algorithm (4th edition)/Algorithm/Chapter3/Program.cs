using StandardLibraries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Chapter3
{
    class Program
    { 
        void FrequencyCounter()
        {
           ISearchTable<string, int> searchTable = null;

            var file = File.OpenRead("tale.txt");
            Scanner scanner = new Scanner(new StreamReader(file));
            Dictionary<string, int> dic = new Dictionary<string, int>();
            StopWatch stopWatch = new StopWatch();
          while(scanner.HasNext())
            {
                var word = scanner.Read();
                //if (word.Length <= 4)
                //    continue;
                if (!dic.ContainsKey(word))
                    dic.Add(word, 1);
                else
                    dic[word]++;
            }
            Console.WriteLine(stopWatch.ElapsedTime );
            var list = dic.Where((keyPair)=>keyPair.Key.Length>3).ToList();
            list.Sort((v1, v2) => v2.Value.CompareTo(v1.Value));
            Console.WriteLine(stopWatch.ElapsedTime );
            int i= 0;
            while(i++<10)
            {
                StdOut.Println(list[i]);
            }
        }
        static void Main(string[] args)
        {
            //StdOut.Println(SearchTableExamples.TimeInput(SearchTableOptions.SequantialST));
           // StdOut.Println(SearchTableExamples.TimeInput(SearchTableOptions.BinarySearchST));
            StdOut.Println(SearchTableExamples.TimeInput(SearchTableOptions.BST,true));
        }
    }
}

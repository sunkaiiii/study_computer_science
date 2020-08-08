using StandardLibraries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Chapter3
{
    class Program
    {

        void SequantialSearchST()
        {
            var file = File.OpenRead("tale.txt");
            Scanner scanner = new Scanner(new StreamReader(file));
            ISearchTable<string, int> dic = new SequantialSearchST<string, int>();
            StopWatch stopWatch = new StopWatch();
            while (scanner.HasNext())
            {
                var word = scanner.Read();
                //if (word.Length <= 4)
                //    continue;
                if (!dic.Contains(word))
                    dic.Put(word, 1);
                else
                    dic.Put(word, dic.Get(word) + 1);
            }
            Console.WriteLine(stopWatch.ElapsedTime);
            foreach(string s in dic.Keys())
            {
                //StdOut.Println(s);
            }
        }

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
            new Program().SequantialSearchST();
        }
    }
}

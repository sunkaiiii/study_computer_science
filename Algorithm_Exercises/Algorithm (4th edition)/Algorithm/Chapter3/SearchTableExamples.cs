using StandardLibraries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Chapter3
{
   public static class SearchTableExamples
    {
        public static double TimeInput(SearchTableOptions options,bool showItems=false)
        {
            var file = File.OpenRead("tale.txt");
            Scanner scanner = new Scanner(new StreamReader(file));
            ISearchTable<string, int> dic;
            new SequantialSearchST<string, int>();
            switch (options)
            {
                case SearchTableOptions.SequantialST:
                    dic = new SequantialSearchST<string,int>();
                    break;
                case SearchTableOptions.BinarySearchST:
                    dic = new BinarySearchST<string, int>();
                    break;
                default:
                    throw new NotImplementedException();
            }
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
            double time =  stopWatch.ElapsedTime;
            if(showItems)
            {
                foreach(var key in dic.Keys())
                {
                    StdOut.Print(key + ",");
                }
            }
            return time;
        }
    }
}

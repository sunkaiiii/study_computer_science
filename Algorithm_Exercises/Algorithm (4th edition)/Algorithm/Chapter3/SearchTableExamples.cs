using StandardLibraries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Chapter3
{
   public static class SearchTableExamples
    {
        public static double TimeInputForHashST(HashTableOptions options)
        {
            var file = File.OpenRead("tale.txt");
            Scanner scanner = new Scanner(new StreamReader(file));
            StopWatch stopWatch = new StopWatch();
            IHashTable<string, int> hashTable = options switch
            {
                HashTableOptions.LinearProbiningHash => new LinearProbingHashST<string, int>(),
                HashTableOptions.SeparateChainingHash => new SeparateChainingHashST<string, int>(),
                _ => throw new Exception("Cannot find the options")
            };
            while (scanner.HasNext())
            {
                var word = scanner.Read();
                hashTable.Put(word, hashTable.Get(word) + 1);
            }
            double time = stopWatch.ElapsedTime;
            return time;
        }
        public static double TimeInput(SearchTableOptions options,bool showItems=false)
        {
            var file = File.OpenRead("tale.txt");
            Scanner scanner = new Scanner(new StreamReader(file));
            ISearchTable<string, int> searchTable = CreateSearchTable<string,int>(options);
            StopWatch stopWatch = new StopWatch();
            while (scanner.HasNext())
            {
                var word = scanner.Read();
                //if (word.Length <= 4)
                //    continue;
                if (!searchTable.Contains(word))
                    searchTable.Put(word, 1);
                else
                    searchTable.Put(word, searchTable.Get(word) + 1);
            }
           
            if(showItems)
            {
                foreach(var key in searchTable.Keys())
                {
                    searchTable.Get(key);
                }
            }
            double time = stopWatch.ElapsedTime;
            return time;
        }

        private static ISearchTable<Key,Value> CreateSearchTable<Key,Value>(SearchTableOptions options) where Key:IComparable<Key>
        {
            ISearchTable<Key, Value> table = options switch
            {
                SearchTableOptions.SequantialST => new SequantialSearchST<Key, Value>(),
                SearchTableOptions.BinarySearchST => new BinarySearchST<Key, Value>(),
                SearchTableOptions.BST => new BST<Key, Value>(),
                SearchTableOptions.RedBlack=>new RedBlackBST<Key,Value>(),
                _ => throw new NotImplementedException(),
            };
            return table;
        }
    }
}

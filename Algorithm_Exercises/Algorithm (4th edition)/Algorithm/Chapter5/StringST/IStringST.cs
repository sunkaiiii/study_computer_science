using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringST
{
    interface IStringST<Value>
    {
        void Put(string key, Value val);
        Value Get(string key);
        void Delete(string key);
        bool Contains(string key);
        bool IsEmpty { get; }
        string LongestPrefixOf(string s); //s的前缀中最长的键
        IEnumerable<string> KeysWithPrefix(string s); //所有以s为前缀的键
        IEnumerable<string> KeysThatMatch(string s); //所有和s匹配的键
        int Size { get; }
        IEnumerable<string> Keys();
    }
}

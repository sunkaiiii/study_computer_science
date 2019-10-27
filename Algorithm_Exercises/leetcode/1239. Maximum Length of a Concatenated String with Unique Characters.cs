using System;
using System.Collections.Generic;

namespace algorithm
{
    //Time Limit Exceeded


//    Given an array of strings arr.String s is a concatenation of a sub-sequence of arr which have unique characters.

//Return the maximum possible length of s.
//Input: arr = ["un","iq","ue"]
//Output: 4
//Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
//Maximum length is 4.
    class Program
    {
        int result;
        HashSet<char> temp;
        void f(IList<string> arr,int i,int remainLength,int rel)
        {
            //Console.WriteLine(i + "," + temp.Count+","+result+","+remainLength);
            if(temp.Count+rel<=result)
            {
                return;
            }
            if(result==remainLength)
            {
                return;
            }
            if(i==arr.Count)
            {
                if(temp.Count>result)
                {
                    result = temp.Count;
                }
                return;
            }
            for(int j=i;j<arr.Count&&result<remainLength;j++)
            {
                string s = arr[j];
                bool ok = true ;
                foreach(char c in s)
                {
                    if(temp.Contains(c))
                    {
                        ok = false;
                        break;
                    }
                }
                if(ok)
                {
                    foreach(char c in s)
                    {
                        temp.Add(c);
                    }
                    f(arr, i + 1,remainLength,rel-s.Length);
                    foreach(char c in s)
                    {
                        temp.Remove(c);
                    }
                }
                f(arr, i + 1,remainLength,rel);
            }
        }
        public int MaxLength(IList<string> arr)
        {
            temp = new HashSet<char>();
            HashSet<char> dd = new HashSet<char>();
            var list = new List<String>();
            foreach(var s in arr)
            {
                int oldCount = dd.Count;
                var hs = new HashSet<int>();
                foreach (char c in s)
                {
                    hs.Add(c);
                }
                if (hs.Count < s.Length)
                {
                    continue;
                }
                list.Add(s);
                foreach (char c in s)
                {
                    dd.Add(c);
                }
                
            }
            int allLength = dd.Count;
            f(list, 0,allLength,allLength);
            return result;
        }
        static void Main(string[] args)
        {
            Console.WriteLine(new Program().MaxLength(new List<string> { "rcoisftjvbp", "mojwnylprskztca", "wbhzkpgsrjvixlafdmn", "arwvtdgnmkxslj", "nykuetwopfi", "aestclfxrhvmuqypo", "dyzaswbmnlrvftgouq", "xniavwocusmlkd", "hearcotfpnglqjwduvk" }));
        }
    }
}

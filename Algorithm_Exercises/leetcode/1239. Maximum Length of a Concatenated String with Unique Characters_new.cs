using System;
using System.Collections.Generic;
using System.Linq;

namespace algorithm
{

//    Given an array of strings arr.String s is a concatenation of a sub-sequence of arr which have unique characters.
//Return the maximum possible length of s.
//Input: arr = ["un","iq","ue"]
//Output: 4
//Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
//Maximum length is 4.
    class Program
    {
        public int MaxLength(IList<string> arr)
        {
            List<string> dp = new List<string>();
            dp.Add("");
            foreach(string a in arr)
            {
                if (a.ToHashSet().Count() != a.Length)
                {
                    continue;
                }
                var temp = new List<string>();
                foreach(var c in dp)
                {
                    if(!c.Intersect(a).Any())
                    {
                        temp.Add(c + a);
                    }
                }
                dp.AddRange(temp);
            }
            return dp.Count == 0 ? 0 : dp.Max(a => a.Length);
        }
        static void Main(string[] args)
        {
            Console.WriteLine(new Program().MaxLength(new List<string> { "xdvqiefpcs", "vgnacw", "raobcnwgufztdykmsvlj" }));
        }
    }
}

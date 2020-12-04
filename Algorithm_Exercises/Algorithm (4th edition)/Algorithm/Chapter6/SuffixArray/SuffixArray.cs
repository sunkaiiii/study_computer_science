using System;
using Chapter2;

namespace Chapter6.SuffixArray
{
    public class SuffixArray
    {
        private readonly string[] suffixes;
        private readonly int N;
        public SuffixArray(string s)
        {
            N = s.Length;
            suffixes = new string[N];
            for (int i = 0; i < N; i++)
            {
                suffixes[i] = s.Substring(i);
            }
            SortExample.ImprovedThreeWayQuickSort(ref suffixes);
        }

        public int Length => N;
        public string Select(int i) => suffixes[i];
        public int Index(int i) => N - suffixes[i].Length;


        private static int Lcp(string s, string t)
        {
            int N = Math.Min(s.Length, t.Length);
            for (int i = 0; i < N; i++)
            {
                if (s[i] != t[i])
                    return i;
            }
            return N;
        }


        public int Lcp(int i)
        {
            return Lcp(suffixes[i], suffixes[i - 1]);
        }

        public int Rank(string key)
        {
            int lo = 0, hi = N - 1;
            while(lo<=hi)
            {
                int mid = lo + (hi - lo) / 2;
                int cmp = key.CompareTo(suffixes[mid]);
                if (cmp < 0)
                    hi = mid - 1;
                if (cmp > 0)
                    lo = mid + 1;
                else
                    return mid;
            }
            return lo;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringSort
{
    public static class Quick3String
    {
        private static int CharAt(string s, int d)
        {
            if (d < s.Length)
                return s[d];
            else
                return -1;
        }

        public static void Sort(string[] a)
        {
            Sort(a, 0, a.Length - 1, 0);
        }
        private static void Exchange(string[] a, int i, int j)
        {
            var t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        private static void Sort(string[] a,int lo,int hi,int d)
        {
            if (hi <= lo)
                return;
            int lt = lo, gt = hi;
            int v = CharAt(a[lo], d);
            int i = lo + 1;
            while(i<=gt)
            {
                int t = CharAt(a[i], d);
                if (t < v)
                    Exchange(a, lt++, i++);
                else if (t > v)
                    Exchange(a, i, gt--);
                else
                    i++;
            }
            //永远是三个方向，避免了小的数组递归出现
            Sort(a, lo, lt - 1, d);
            if (v >= 0)
                Sort(a, lt, gt, d + 1);
            Sort(a, gt + 1, hi, d);
        }
    }
}

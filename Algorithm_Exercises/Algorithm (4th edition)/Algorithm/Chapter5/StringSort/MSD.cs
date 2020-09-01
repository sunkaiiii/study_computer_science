using Chapter2;
using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace Chapter5.StringSort
{
    //高位有限字符串排序
   public  class MSD
    {
        private static int R = 256; //基数
        private static readonly int M = 15; //小数组切换的阈值
        private static string[] aux; //数组分类的辅助数组
        private static int CharAt(string s, int d)
        {
            if (d < s.Length)
                return s[d];
            else
                return -1;
        }

        public static void Sort(string[] a)
        {
            int N = a.Length;
            aux = new string[N];
            Sort(a, 0, N - 1, 0); //类似快速排序
        }

        private static void Sort(string[] a, int lo, int hi, int d)
        {
           //以d个字符为键将a[lo]至a[hi]排序
           if(hi<=lo+M)
            {
                SortExample.InsertionSort(ref a, lo, hi);
                return;
            }
            int[] count = new int[R + 2];
            for (int i = lo; i <= hi; i++) //计算频率
                count[CharAt(a[i], d) + 2]++;
            for (int r = 0; r < R + 1; r++) //频率转换为索引
                count[r + 1] += count[r];
            for (int i = lo; i <= hi; i++)//数据分类
                aux[count[CharAt(a[i], d) + 1]++] = a[i];
            for (int i = lo; i < hi; i++)
                a[i] = aux[i - lo];
            //递归的以每个字符为键进行排序
            for (int i = 0; i < R; i++)
            {
                Sort(a, lo + count[i], lo + count[i + 1] - 1, d + 1);
            }
        }
    }
}

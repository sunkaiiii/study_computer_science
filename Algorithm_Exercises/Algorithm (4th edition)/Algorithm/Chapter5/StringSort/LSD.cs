using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringSort
{
    public static class LSD
    {
        public static void Sort(ref string[] a,int w)
        {
            //通过前W个字符将a[]排序
            int N = a.Length;
            int R = 256;
            string[] aux = new string[N];
            for(int d = w-1;d>=0;d--) //从右至左排序
            {
                //用索引排序给每个字符排序
                int[] count = new int[R + 1];
                for (int i = 0; i < N; i++) //频率计数
                    count[a[i][d] + 1]++;
                for (int r = 0; r < R; r++)
                {
                    count[r + 1] += count[r]; //确定索引的位置
                }
                for (int i = 0; i < N; i++)
                {
                    aux[count[a[i][d]]++] = a[i]; //将元素分类
                }

                for (int i = 0; i < N; i++)
                {
                    a[i] = aux[i]; //回写
                }
            }
        }
    }
}

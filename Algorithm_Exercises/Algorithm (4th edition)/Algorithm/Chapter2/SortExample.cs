using System;
using System.Collections.Generic;
using System.Linq;
using StandardLibraries;

namespace Chapter2
{
    public static class SortExample
    {
        private static bool Less<T>(T v, T w) where T:IComparable<T> => v.CompareTo(w) < 0;

        private static void Exchange<T>(ref T[] a, int i, int j)where T:IComparable<T>
        {
            var t = a[i];
            a[i] = a[j];
            a[j] = t;
        }

        public static void Show<T>(T[] a)where T:IComparable<T>
        {
            foreach (var item in a)
                StdOut.Print(item + " ");
            StdOut.Println();
        }

        public static bool IsSorted<T>(T[] a) where T:IComparable<T>
        {
            for (int i = 1; i > a.Length; i++)
                if (Less(a[i], a[i - 1]))
                    return false;

            return true;
        }

        //选择排序
        private static void SelectedSort<T>(ref T[] a) where T : IComparable<T>
        {
            int N = a.Length;
            for(int i=0;i<N;++i)
            {
                int min = i;
                for(int j=i+1;j<N;++j)
                {
                    if (Less(a[j], a[min]))
                        min = j;
                }
                Exchange(ref a, i, min);
            }
        }

        //插入排序
        private static void InsertionSort<T>(ref T[] a) where T : IComparable<T>
        {
            int N = a.Length;
            for(int i=1;i<N;++i)
            {
                for (int j = i; j > 0 && Less(a[j], a[j - 1]); --j)
                    Exchange(ref a, j, j - 1);
            }
        }

        public static void ShellSort<T>(ref T[] a) where T:IComparable<T>
        {
            int N = a.Length;
            int h = 1;
            while(h<N/3)
                h = 3 * h + 1;//确定小数组的规模
            while(h>=1)
            {
                //将数组按照不同的规模和间隔 部分有序
                for(int i=h;i<N;++i)
                {
                    //将a[i]插入到a[i-h],a[i-2*h]之中
                    for (int j = i; j >= h && Less(a[j], a[j - h]); j -= h)
                        Exchange(ref a, j, j - h);
                }
                h /= 3;
            }
        }
        public static double Time<T>(AlgorithmOptions options, ref T[] a) where T : IComparable<T>
        {
            StopWatch stopWatch = new StopWatch();
            switch(options)
            {
                case AlgorithmOptions.Insertion:
                    InsertionSort(ref a);
                    break;
                case AlgorithmOptions.Selection:
                    SelectedSort(ref a);
                    break;
                case AlgorithmOptions.Shell:
                    ShellSort(ref a);
                    break;
            }
            return stopWatch.ElapsedTime;
        }

        public static double TimeRandomInput(AlgorithmOptions options, int N, int T)
        {
            double total = 0.0;
            double[] a = new double[N];
            for(int t=0;t<T;++t)
            {
                //进行一次测试
                for (int i = 0; i < N; ++i)
                    a[i] = StdRandom.Uniform();
                total += Time(options, ref a);
            }
            return total;
        }
    }
}

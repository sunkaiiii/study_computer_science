using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using StandardLibraries;

namespace Chapter2
{
    public static class SortExample
    {
        private static bool Less<T>(T v, T w) where T : IComparable<T> => v.CompareTo(w) < 0;

        private static void Exchange<T>(ref T[] a, int i, int j) where T : IComparable<T>
        {
            var t = a[i];
            a[i] = a[j];
            a[j] = t;
        }

        public static void Show<T>(T[] a) where T : IComparable<T>
        {
            foreach (var item in a)
                StdOut.Print(item + " ");
            StdOut.Println();
        }

        public static bool IsSorted<T>(T[] a) where T : IComparable<T>
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
            for (int i = 0; i < N; ++i)
            {
                int min = i;
                for (int j = i + 1; j < N; ++j)
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
            for (int i = 1; i < N; ++i)
            {
                for (int j = i; j > 0 && Less(a[j], a[j - 1]); --j)
                    Exchange(ref a, j, j - 1);
            }
        }

        private static void InsertionSort<T>(ref T[] a, int lo, int hi) where T : IComparable<T>
        {
            int N = hi;
            for (int i = lo + 1; i < hi; ++i)
            {
                for (int j = i; j > lo && Less(a[j], a[j - 1]); --j)
                    Exchange(ref a, j, j - 1);
            }
        }

        public static void ShellSort<T>(ref T[] a) where T : IComparable<T>
        {
            int N = a.Length;
            int h = 1;
            while (h < N / 3)
                h = 3 * h + 1;//确定小数组的规模
            while (h >= 1)
            {
                //将数组按照不同的规模和间隔 部分有序
                for (int i = h; i < N; ++i)
                {
                    //将a[i]插入到a[i-h],a[i-2*h]之中
                    for (int j = i; j >= h && Less(a[j], a[j - h]); j -= h)
                        Exchange(ref a, j, j - h);
                }
                h /= 3;
            }
        }

        public static void MergeSort<T>(ref T[] a) where T : IComparable<T>
        {
            T[] aux = new T[a.Length];
            MergeSort(ref a, ref aux, 0, a.Length - 1);
        }

        private static void MergeSort<T>(ref T[] a, ref T[] aux, int lo, int hi) where T : IComparable<T>
        {
            if (hi <= lo)
                return;
            int mid = lo + (hi - lo) / 2;
            MergeSort(ref a, ref aux, lo, mid);
            MergeSort(ref a, ref aux, mid + 1, hi);
            Merge(ref a, ref aux, lo, mid, hi);

        }

        private static void MergeSortNonRecursive<T>(ref T[] a) where T : IComparable<T>
        {
            int N = a.Length;
            T[] aux = new T[a.Length];
            for (int sz = 1; sz < N; sz = sz + sz) //子数组大小
                for (int lo = 0; lo < N - sz; lo += sz + sz) //子数组索引
                    Merge(ref a, ref aux, lo, lo + sz - 1, Math.Min(lo + sz + sz - 1, N - 1));
        }

        private static void ImprovedMerge<T>(ref T[] a) where T : IComparable<T>
        {
            T[] aux = new T[a.Length];
            ImprovedMerge(ref a, ref aux, 0, a.Length - 1);
        }

        private static void ImprovedMerge<T>(ref T[] a, ref T[] aux, int lo, int hi) where T : IComparable<T>
        {
            if (hi <= lo)
                return;
            int mid = lo + (hi - lo) / 2;
            ImprovedMerge(ref a, ref aux, lo, mid);
            ImprovedMerge(ref a, ref aux, mid + 1, hi);
            if (a[mid].CompareTo(a[mid + 1]) <= 0) //当[mid]小于等于a[mid+1]的时候，可以认为数组已经有序了，跳过merge方法
                return;
            Merge(ref a, ref aux, lo, mid, hi);
        }

        private static void QuickSort<T>(ref T[] a) where T : IComparable<T>
        {
            StdRandom.Shuffle(ref a); //消除对于输入的依赖
            QuickSort(ref a, 0, a.Length - 1);
        }

        private static void QuickSort<T>(ref T[] a, int lo, int hi) where T : IComparable<T>
        {
            if (hi <= lo)
                return;
            int j = Partitioner(ref a, lo, hi); //切分
            QuickSort(ref a, lo, j - 1); //左半部分排序
            QuickSort(ref a, j + 1, hi); //右半部分排序
        }

        private static void ImprovedQuickSort<T>(ref T[] a) where T : IComparable<T>
        {
            StdRandom.Shuffle(ref a);
            ImprovedQuickSort(ref a, 0, a.Length - 1);
        }
        private static void ImprovedQuickSort<T>(ref T[] a, int lo, int hi) where T : IComparable<T>
        {
            int M = 10; //选择小数组的大小，一般5-15都可以做到比较令人满意的提升
            if (hi <= lo + M)
            {
                InsertionSort(ref a, lo, hi); //排序小数组，应该使用插入排序
                return;
            }
            int j = Partitioner(ref a, lo, hi); //切分
            ImprovedQuickSort(ref a, lo, j - 1); //左半部分排序
            ImprovedQuickSort(ref a, j + 1, hi); //右半部分排序
        }
        private static void ImprovedThreeWayQuickSort<T>(ref T[] a) where T : IComparable<T>
        {
            StdRandom.Shuffle(ref a);
            ImprovedThreeWayQuickSort(ref a, 0, a.Length - 1);
        }
        private static void ImprovedThreeWayQuickSort<T>(ref T[] a, int lo, int hi) where T : IComparable<T>
        {
            int M = 10;
            if (hi <= lo + M)
            {
                InsertionSort(ref a, lo, hi);
                return;
            }
            //三向切分快速排序,对于大量重复的数组元素，这个效率快很多
            int lt = lo, i = lo + 1, gt = hi;
            T v = a[lo];
            while (i <= gt)
            {
                int cmp = a[i].CompareTo(v);
                if (cmp < 0)
                    Exchange(ref a, lt++, i++);
                else if (cmp > 0)
                    Exchange(ref a, i, gt--);
                else
                    i++;
            }
            ImprovedThreeWayQuickSort(ref a, lo, lt - 1);
            ImprovedThreeWayQuickSort(ref a, gt + 1, hi);
        }
        private static int Partitioner<T>(ref T[] a, int lo, int hi) where T : IComparable<T>
        {
            int i = lo;
            int j = hi + 1; //左右扫描的指针
            T v = a[lo]; //切分元素
            while (true)
            {
                //扫描左右，检查扫描是否结束并交换元素
                while (Less(a[++i], v))
                    if (i == hi)
                        break;
                while (Less(v, a[--j]))
                    if (j == lo)
                        break;
                if (i >= j)
                    break;
                Exchange(ref a, i, j);
            }
            Exchange(ref a, lo, j); //将v=a[j]放入正确的位置
            return j;
        }

        private static void Merge<T>(ref T[] a, ref T[] aux, int lo, int mid, int hi) where T : IComparable<T>
        {
            int i = lo;
            int j = mid + 1;
            for (int k = lo; k <= hi; k++) //区间的所有元素a[lo..hi]复制到[lo..hi]
                aux[k] = a[k];
            for (int k = lo; k <= hi; k++) //归并到a[lo..hi]
                if (i > mid) //左边条件用完
                    a[k] = aux[j++];
                else if (j > hi) //右边条件用完
                    a[k] = aux[i++];
                else if (Less(aux[j], aux[i])) //右边小 
                    a[k] = aux[j++];
                else //左边小
                    a[k] = aux[i++];
        }

        public static void HeapSort<T>(ref T[] a) where T : IComparable<T>
        {
            MaxPQ<T> maxPQ = new MaxPQ<T>(a);
            maxPQ.Sort();
            T[] pq = maxPQ.Get();
            for (int i = 1; i < pq.Length; i++)
                a[i - 1] = pq[i];
        }

        public static double Time<T>(AlgorithmOptions options, ref T[] a, bool showResult) where T : IComparable<T>
        {
            StopWatch stopWatch = new StopWatch();
            if (showResult)
                Show(a);
            switch (options)
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
                case AlgorithmOptions.Merge:
                    MergeSort(ref a);
                    break;
                case AlgorithmOptions.NonRecursiveMerge:
                    MergeSortNonRecursive(ref a);
                    break;
                case AlgorithmOptions.ImprovedMerge:
                    ImprovedMerge(ref a);
                    break;
                case AlgorithmOptions.Quick:
                    QuickSort(ref a);
                    break;
                case AlgorithmOptions.ImprovedQuick:
                    ImprovedQuickSort(ref a);
                    break;
                case AlgorithmOptions.ImprovedThreeWayQuick:
                    ImprovedThreeWayQuickSort(ref a);
                    break;
                case AlgorithmOptions.Heap:
                    HeapSort(ref a);
                    break;
                case AlgorithmOptions.System:
                    Array.Sort(a);
                    break;
            }
            if (showResult)
                Show(a);
            return stopWatch.ElapsedTime;
        }

        public static double TimeRandomInput(AlgorithmOptions options, int N, int T, bool showResult = false)
        {
            StdOut.Print("Algorithm: " + options.ToString() + " "+"Sorting "+N+" number for "+T+" times ");
            double total = 0.0;
            double[] a = new double[N];
            for (int t = 0; t < T; ++t)
            {
                //进行一次测试
                for (int i = 0; i < N; ++i)
                    a[i] = StdRandom.Uniform();
                total += Time(options, ref a, showResult);
            }
            return total;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter2
{
    interface IPriorityQueue<T> where T:IComparable<T>
    {
        void Insert(T v);
        T Top();
        T Delete();
        bool IsEmpty { get; }
        int Size { get; }
    }
}

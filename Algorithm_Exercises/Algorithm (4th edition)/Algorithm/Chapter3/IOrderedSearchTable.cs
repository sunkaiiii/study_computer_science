using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    interface IOrderedSearchTable<Key,Value>:ISearchTable<Key,Value> where Key:IComparable<Key>
    {
        Key Min { get; }
        Key Max { get; }
        Key Fllor(Key key); //小于等于key的最大键
        Key Ceiling(Key key); //大于等于key的最小键
        //所有的i都满足i==rank(select(i))
        //所有的键都满足key==select(rank(key))
        int Rank(Key key); //小于key键的数量
        Key Select(int k); //排名为k的键
        void DeleteMin()
        {
            Delete(Min);
        }
        void DeleteMax()
        {
            Delete(Max);
        }
        new int Size(Key lo, Key hi)
        {
            if (hi.CompareTo(lo) < 0)
                return 0;
            else if (Contains(hi))
                return Rank(hi) - Rank(lo) + 1;
            else
                return Rank(hi) - Rank(lo);
        }
        IEnumerable<Key> Keys(Key lo, Key hi);

        new IEnumerable<Key> Keys()
        {
            return Keys(Min, Max);
        }
    }
}

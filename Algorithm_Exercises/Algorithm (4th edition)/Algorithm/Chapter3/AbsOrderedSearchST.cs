using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    abstract class AbsOrderedSearchST<Key, Value> : IOrderedSearchTable<Key, Value> where Key:IComparable<Key>
    {
        public bool Contains(Key key)
        {
            return Get(key) != null;
        }

        public bool IsEmpty
        {
            get
            {
                return Size == 0;
            }
        }

        public void DeleteMin()
        {
            Delete(Min);
        }

        public void DeleteMax()
        {
            Delete(Max);
        }

        public int GetSize(Key lo, Key hi)
        {
            if (hi.CompareTo(lo) < 0)
                return 0;
            else if (Contains(hi))
                return Rank(hi) - Rank(lo) + 1;
            else
                return Rank(hi) - Rank(lo);
        }

        public IEnumerable<Key> Keys()
        {
            return Keys(Min, Max);
        }

        public abstract Key Min { get; }
        public abstract Key Max { get; }

        public int Size { get; protected set; } = 0;

        public abstract void Put(Key key, Value value);
        public abstract Value Get(Key key);
        public abstract Key Floor(Key key);
        public abstract Key Ceiling(Key key);
        public abstract int Rank(Key key);
        public abstract Key Select(int k);

        public abstract IEnumerable<Key> Keys(Key lo, Key hi);
        public abstract void Delete(Key key);
    }
}

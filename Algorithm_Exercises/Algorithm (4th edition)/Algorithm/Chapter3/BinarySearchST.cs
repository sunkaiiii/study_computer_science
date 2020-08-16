using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    class BinarySearchST<Key, Value> : AbsOrderedSearchST<Key, Value> where Key : IComparable<Key>
    {
        private Key[] keys;
        private Value[] vals;
        public override Key Max => keys[Size - 1];
        public override Key Min => keys[0];

        public override int Size { get; protected set; } = 0;

        public BinarySearchST(int capacity=16)
        {
            keys = new Key[capacity];
            vals = new Value[capacity];
        }

        public override Value Get(Key key)
        {
            if (IsEmpty)
                return default;
            int i = Rank(key);
            if (i < Size && keys[i].CompareTo(key) == 0)
                return vals[i];
            return default;
        }

        public override void Put(Key key, Value value)
        {
            if(Size+1>=keys.Length)
            {
                ResizeArray();
            }
            int i = Rank(key);//查找index
            if(i<Size&&keys[i].CompareTo(key)==0)
            {
                vals[i] = value;
                return;
            }
            for(int j=Size;j>i;j--)
            {
                //把插入位置的数组的元素都向后推移
                keys[j] = keys[j - 1];
                vals[j] = vals[j - 1];
            }
            keys[i] = key;
            vals[i] = value;
            Size++;
        }

        private void ResizeArray()
        {
            Key[] newKey = new Key[keys.Length * 2];
            Value[] newValue = new Value[vals.Length * 2];
            Array.Copy(keys, newKey, keys.Length);
            Array.Copy(vals, newValue, vals.Length);
            keys = newKey;
            vals = newValue;
        }

        public override int Rank(Key key)
        {
            //二分查找
            int lo = 0, hi = Size - 1; 
            while(lo<=hi)
            {
                int mid = lo + (hi - lo) / 2;
                int cmp = key.CompareTo(keys[mid]);
                if (cmp < 0)
                    hi = mid - 1;
                else if (cmp > 0)
                    lo = mid + 1;
                else return mid;
            }
            return lo;
        }

        public override Key Select(int k)
        {
            return keys[k];
        }

        public override Key Ceiling(Key key)
        {
            int i = Rank(key);
            return keys[i];
        }

        public override IEnumerable<Key> Keys(Key lo, Key hi)
        {
            Queue<Key> q = new Queue<Key>();
            var left = Rank(lo);
            var right = Rank(hi);
            for(int i=left;i<right;i++)
            {
                q.Enqueue(keys[i]);
            }
            if (Contains(hi))
                q.Enqueue(keys[right]);
            return q;
        }

        public override Key Floor(Key key)
        {
            int i = Rank(key);
            if (keys[i].CompareTo(key) > 0 && i + 1 < Size)
                return keys[i + 1];
            else if (keys[i].CompareTo(key) > 0)
                return default;
            return keys[i];
        }

        public override void Delete(Key key)
        {
            int i = Rank(key);
            for(;i+1<Size;i++)
            {
                keys[i] = keys[i + 1];
                vals[i] = vals[i + 1];
                if (i + 2 == Size)
                {
                    keys[i + 1] = default;
                    vals[i + 1] = default;
                }
            }
            Size--;
        }
    }
}

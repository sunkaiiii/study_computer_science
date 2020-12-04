using System;
namespace Chapter6.BTree
{
    public class BTreeSET<Key> where Key:IComparable<Key>
    {
        private IPage<Key> Root { get; set; }

        public BTreeSET(Key sentinel)
        {
            Root = CreateNewNode();
            Add(sentinel);
        }

        public bool Contains(Key key)
        {
            return Contains(Root, key);
        }

        private bool Contains(IPage<Key> h, Key key)
        {
            if(h.IsExternal())
            {
                return h.Contains(key);
            }
            return Contains(h.Next(key), key);
        }

        public void Add(Key key)
        {
            Add(Root, key);
            if(Root.IsFull())
            {
                var leftHalf = Root;
                var rightHalf = Root.Split();
                Root = CreateNewNode();
                Root.Add(leftHalf);
                Root.Add(rightHalf);
            }
        }

        public void Add(IPage<Key> h,Key key)
        {
            if(h.IsExternal())
            {
                h.Add(key);
                return;
            }
            var next = h.Next(key);
            Add(next, key);
            if(next.IsFull())
            {
                h.Add(next.Split());
            }
            next.Close();
        }

        private IPage<Key> CreateNewNode()
        {
            //TODO needs to be implemented
            return null;
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    class SequantialSearchST<Key, Value> : ISearchTable<Key, Value>
    {
        private Node first;
        public int Size { get; private set; } = 0;

        public bool IsEmpty => Size == 0;

        class Node
        {
            public Key Key { get; set; }
            public Value Value { get; set; }
            public  Node Next { get; set; }
            public Node(Key key,Value value,Node next)
            {
                this.Key = key;
                this.Value = value;
                this.Next = next;
            }
        }

        public Value Get(Key key)
        {
            for(Node x = first;x!=null;x=x.Next)
            {
                if (key.Equals(x.Key))
                    return x.Value;
            }
            return default;
        }

        public IEnumerable<Key> Keys()
        {
            return new KeyEnumerable(first);
        }

        private class KeyEnumerable : IEnumerable<Key>
        {
            private Node first;

            public KeyEnumerable(Node first)
            {
                this.first = first;
            }

            public IEnumerator<Key> GetEnumerator()
            {
                return new KeyEnumerator(first);
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return new KeyEnumerator(first);
            }
        }

        private class KeyEnumerator : IEnumerator<Key>
        {
            private Node First { get; set; }
            private Node Cur { get; set; }
            public KeyEnumerator(Node first)
            {
                this.First = first;
            }
            public Key Current => Cur.Key;

            object IEnumerator.Current => Cur.Key;

            public void Dispose()
            {
                Cur = null;
                First = null;
            }

            public bool MoveNext()
            {
                if (Cur == null)
                    Cur = First;
                else
                    Cur = Cur.Next;
                return Cur != null;
            }

            public void Reset()
            {
                Cur = First;
            }
        }

        public void Put(Key key, Value value)
        {
            for(Node x=first;x!=null;x=x.Next)
            {
                if(key.Equals(x.Key))
                {
                    x.Value = value;
                    return;
                }
            }
            first = new Node(key, value, first); //未命中，创建新节点
            Size++;
        }

        public bool Contains(Key key)
        {
            return Get(key) != null;
        }

        public void Delete(Key key)
        {
            Put(key, default(Value)); //延迟删除的默认实现
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Chapter1
{
    public class Bag<T>: IEnumerable<T>
    {
        private Node<T> first;

        public void Add(T item)
        {
            Node<T> oldfirst = first;
            first = new Node<T>();
            first.Item = item;
            first.Next = oldfirst;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new BagEnumerator<T>(first);
        }


        IEnumerator IEnumerable.GetEnumerator()
        {
            return new BagEnumerator<T>(first);
        }

        private class BagEnumerator<T> : IEnumerator<T>
        {
            public Node<T> first;
            public Node<T> current;
            public BagEnumerator(Node<T> first)
            {
                this.first = first;
            }

            public T Current =>current.Item;

            object IEnumerator.Current => current.Item;

            public void Dispose()
            {
                current = null;
                first = null;
            }

            public bool MoveNext()
            {
                if (current == null)
                    current = first;
                else 
                    current = current.Next;
                return current != null;
            }

            public void Reset()
            {
                current=first;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter1
{
    public class Queue<T>
    {
        private Node<T> first;
        private Node<T> last;
        private int N { get; set; }
        public bool IsEmpty { get { return N == 0; } }
        public int Size { get { return N; } }
        
        public void Enqueue(T item)
        {
            Node<T> oldlast = last;
            last = new Node<T>();
            last.Item = item;
            last.Next = null;
            if (IsEmpty)
                first = last;
            else
                oldlast.Next = last;
            N++;
        }

        public T Dequeue()
        {
            T item = first.Item;
            first = first.Next;
            if (IsEmpty)
                last = null;
            N--;
            return item;
        }
    }
}

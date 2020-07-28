using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter1
{
    //下压堆栈，链表实现
    public class Stack<T>
    {
        private Node<T> first;
        private int N { get; set; }
        public bool IsEmpty { get { return first == null; } }
        public int Size { get { return N; } }
        
        public void Push(T item)
        {
            Node<T> oldfirst = first;
            first = new Node<T>();
            first.Item = item;
            first.Next = oldfirst;
            N++;
        }

        public T pop()
        {
            T item = first.Item;
            first = first.Next;
            N--;
            return item;
        }

        public T Peek()
        {
            if(first!=null&&first.Next!=null)
            {
                return first.Next.Item;
            }
            return default(T);
        }
    }
}

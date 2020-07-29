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

        public Stack() { }

        public Stack(Stack<T> oldStack)
        {
            T[] items = new T[oldStack.Size];
            int index = oldStack.Size - 1;
            while(!oldStack.IsEmpty)
            {
                items[index--] = oldStack.Pop();
            }
            foreach(var item in items)
            {
                oldStack.Push(item);
                Push(item);
            }
        }
        
        public void Push(T item)
        {
            Node<T> oldfirst = first;
            first = new Node<T>();
            first.Item = item;
            first.Next = oldfirst;
            N++;
        }

        public T Pop()
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

        public void Reverse()
        {
            var first = this.first;
            Node<T> reverse = null;
            while(first != null)
            {
                var second = first.Next;
                first.Next = reverse;
                reverse = first;
                first = second;
            }
            this.first = reverse;
        }
    }
}

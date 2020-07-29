using System;
namespace Chapter1
{
    public class Deque<T>
    {
        private DequeNode<T> first;
        private DequeNode<T> last;
        private int N { get; set; }
        public bool IsEmpty => first == null && last == null;
        public int Size => N;
        private class DequeNode<T>
        {
            public T Item { get; set; }
            public DequeNode<T> Left { get; set; }
            public DequeNode<T> Right { get; set; }
        }

        public void PushLeft(T item)
        {
            DequeNode<T> dequeNode = new DequeNode<T>();
            dequeNode.Right = first;
            if(first!=null)
                first.Left = dequeNode;
            first = dequeNode;
            if (last == null)
                last = first;
            dequeNode.Item = item;
            N++;
        }

        public void PushRight(T item)
        {
            DequeNode<T> dequeNode = new DequeNode<T>();
            dequeNode.Left = last;
            if (last != null)
                last.Right = dequeNode;
            last = dequeNode;
            if (first == null)
                first = dequeNode;
            dequeNode.Item = item;
            N++;
        }

        public T PopLeft()
        {
            var current = first;
            if (first.Right != null)
                first.Right.Left = null;
            else
                last = null;
            first = first.Right;
            current.Right = null;
            N--;
            return current.Item;
        }

        public T PopRight()
        {
            var current = last;
            if (last.Left != null)
                last.Left.Right = null;
            else
                first = null;
            last = last.Left;
            current.Left = null;
            N--;
            return current.Item;
        }
    }
}

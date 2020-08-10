using Chapter1;
using System;
using System.Collections.Generic;

namespace Chapter3
{
    class BST<Key,Value>:AbsOrderedSearchST<Key,Value>where Key:IComparable<Key>
    {
        public Node Root { get; private set; }

        public class Node
        {
            public Key Key { get; }
            public Value Val { get; internal set; }
            public Node Left { get; internal set; }
            public Node Right { get; internal set; }
            public int N { get; internal set; } //以该节点为根的子树中的节点总数
            public Node(Key key, Value val, int N)
            {
                this.Key = key;
                this.Val = val;
                this.N = N;
            }
        }
        public new int Size { get
            {
                return GetNodeSize(Root);
            } }

        private int GetNodeSize(Node node)
        {
            if (node == null)
                return 0;
            return node.N;
        }

        public override Key Min => FindMin(Root).Key;

        private Node FindMin(Node x)
        {
            if (x.Left == null)
                return x;
            return FindMin(x.Left);
        }

        public override Key Max => FindMax(Root).Key;

        private Node FindMax(Node x)
        {
            if (x.Right == null)
                return x;
            return FindMax(x.Right);
        }

        public override Key Ceiling(Key key)
        {
            Node x = Ceiling(Root, key);
            if (x == null)
                return default;
            return x.Key;
        }

        private Node Ceiling(Node x, Key key)
        {
            if (x == null)
                return null;
            int cmp = key.CompareTo(x.Key);
            if (cmp == 0)
                return x;
            if (cmp < 0)
                return Ceiling(x.Right, key);
            Node t = Ceiling(x.Left, key);
            if (t != null)
                return t;
            return x;
        }

        public override void Delete(Key key)
        {
            Root = Delete(Root, key);
        }

        private Node Delete(Node x, Key key)
        {
            if(x==null)
            {
                return null;
            }
            int cmp = key.CompareTo(x.Key);
            if (cmp < 0)
                x.Left = Delete(x.Left, key);
            else if (cmp > 0)
                x.Right = Delete(x.Right, key);
            else
            {
                if (x.Right == null)
                    return x.Left;
                if (x.Left == null)
                    return x.Right;
                Node t = x;
                x = FindMin(t.Right);
                x.Right = DeleteMin(t.Right);
                x.Left = t.Left;
            }
            x.N = GetNodeSize(x.Left) + GetNodeSize(x.Right) + 1;
            return x;
        }


        public new void DeleteMin()
        {
            Root = DeleteMin(Root);
        }
        private Node DeleteMin(Node x)
        {
            if (x.Left == null)
                return x.Right;
            x.Left = DeleteMin(x.Left);
            x.N = GetNodeSize(x.Left) + GetNodeSize(x.Right) + 1;
            return x;
        }

        public new void DeleteMax()
        {
            Root = DeleteMax(Root);
        }

        private Node DeleteMax(Node x)
        {
            if (x.Right == null)
                return x.Left;
            x.Right = DeleteMax(x.Right);
            x.N = GetNodeSize(x.Left) + GetNodeSize(x.Right) + 1;
            return x;
        }

        public override Key Floor(Key key)
        {
            Node x = Floor(Root, key);
            if (x == null)
                return default;
            return x.Key;
        }

        private Node Floor(Node x, Key key)
        {
            if (x == null)
                return null;
            int cmp = key.CompareTo(x.Key);
            if (cmp == 0)
                return x;
            if (cmp < 0)
                return Floor(x.Left, key);
            Node t = Floor(x.Right, key);
            if (t != null)
                return t;
            return x;
        }

        public override Value Get(Key key)
        {
            return Get(Root, key);
        }

        private Value Get(Node x, Key key)
        {
            if (x == null)
                return default;
            int cmp = key.CompareTo(x.Key);
            if (cmp < 0)
                return Get(x.Left, key);
            else if (cmp > 0)
                return Get(x.Right, key);
            else
                return x.Val;
        }

        public override IEnumerable<Key> Keys(Key lo, Key hi)
        {
            Chapter1.Queue<Key> queue = new Chapter1.Queue<Key>();
            Keys(Root, queue, lo, hi);
            return queue;
        }

        private void Keys(Node x, Chapter1.Queue<Key> queue, Key lo, Key hi)
        {
            //使用中序遍历进行二叉树的范围查找
            if (x == null)
                return;
            int cmplo = lo.CompareTo(x.Key);
            int cmphi = hi.CompareTo(x.Key);
            if (cmplo < 0)
                Keys(x.Left, queue, lo, hi);
            if (cmplo <= 0 && cmphi >= 0)
                queue.Enqueue(x.Key);
            if (cmphi > 0)
                Keys(x.Right, queue, lo, hi);
        }

        public override void Put(Key key, Value value)
        {
            Root = Put(Root, key, value);
        }

        private Node Put(Node x, Key key, Value value)
        {
            //如果key存在于x为根节点的子树中，则更新
            //否则将以key和val为键值对的新节点插入到子树中
            if (x == null)
                return new Node(key, value, 1);
            int cmp = key.CompareTo(x.Key);
            if (cmp < 0)
                x.Left = Put(x.Left, key, value);
            else if (cmp > 0)
                x.Right = Put(x.Right, key, value);
            else
                x.Val = value;
            x.N = GetNodeSize(x.Left) + GetNodeSize(x.Right) + 1;
            return x;
        }

        public override int Rank(Key key)
        {
            return Rank(key, Root);
        }

        private int Rank(Key key, Node x)
        {
            if (x == null)
                return 0;
            int cmp = key.CompareTo(x.Key);
            if (cmp < 0)
                return Rank(key, x.Left);
            else if (cmp > 0)
                return 1 + GetNodeSize(x.Left) + Rank(key, x.Right);
            else
                return GetNodeSize(x.Left);
        }

        public override Key Select(int k)
        {
            return Select(Root, k).Key;
        }

        private Node Select(Node x, int k)
        {
            if (x == null)
                return null;
            int size = GetNodeSize(x.Left);
            if (size > k)
                return Select(x.Left, k);
            else if (size < k)
                return Select(x.Right, k - size - 1);
            else
                return x;
        }
    }
}

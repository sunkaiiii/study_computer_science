using System;
using System.Collections.Generic;
using System.Net;
using System.Reflection.Metadata.Ecma335;
using System.Text;

namespace Chapter3
{
    public class RedBlackBST<Key,Value>:BST<Key,Value> where Key:IComparable<Key>
    {

        private static readonly bool RED = true;
        private static readonly bool BLACK = false;

        private bool IsRed(RedBlackBSTNode<Key, Value> x) => x != null && x.Color == RED;

        private RedBlackBSTNode<Key, Value> RotateLeft(RedBlackBSTNode<Key, Value> h)
        {
            RedBlackBSTNode<Key, Value> x = (RedBlackBSTNode<Key, Value>)h.Right;
            h.Right = x.Left;
            x.Left = h;
            x.Color = h.Color;
            h.Color = RED;
            x.N = h.N;
            h.N = 1 + GetNodeSize(h.Left) + GetNodeSize(h.Right);
            return x;
        }

        private RedBlackBSTNode<Key, Value> RotateRight(RedBlackBSTNode<Key, Value> h)
        {
            RedBlackBSTNode<Key, Value> x = (RedBlackBSTNode<Key, Value>)h.Left;
            h.Left = x.Right;
            x.Right = h;
            x.Color = h.Color;
            h.Color = RED;
            x.N = h.N;
            h.N = 1 + GetNodeSize(h.Left) + GetNodeSize(h.Right);
            return x;
        }

        public override void Put(Key key, Value value)
        {
            var root = Put((RedBlackBSTNode<Key, Value>)Root, key, value);
            root.Color = BLACK;
            Root = root;
        }

        private RedBlackBSTNode<Key, Value> Put(RedBlackBSTNode<Key, Value> h, Key key, Value value)
        {
            if (h == null) //标准的插入操作，和父节点用红链接相连
                return new RedBlackBSTNode<Key, Value>(key, value, 1, RED);
            int cmp = key.CompareTo(h.Key);
            if (cmp < 0)
                h.Left = Put((RedBlackBSTNode<Key, Value>)h.Left, key, value);
            else if (cmp > 0)
                h.Right = Put((RedBlackBSTNode<Key, Value>)h.Right, key, value);
            else h.Val = value;
            if (IsRed((RedBlackBSTNode<Key, Value>)h.Right) && !IsRed((RedBlackBSTNode<Key, Value>)h.Left)) //左黑右红，左旋转
                h = RotateLeft(h);
            if (IsRed((RedBlackBSTNode<Key, Value>)h.Left) && IsRed((RedBlackBSTNode<Key, Value>)h.Left.Left))//连续两个红，右旋转
                h = RotateRight(h);
            if (IsRed((RedBlackBSTNode<Key, Value>)h.Left) && IsRed((RedBlackBSTNode<Key, Value>)h.Right)) //左右都为红，执行颜色变换
                FlipColours(h);
            h.N = GetNodeSize(h.Left) + GetNodeSize(h.Right) + 1;
            return h;
        }

        private void FlipColours(RedBlackBSTNode<Key, Value> h)
        {
            h.Color = RED;
            ((RedBlackBSTNode<Key, Value>)h.Left).Color = BLACK;
            ((RedBlackBSTNode<Key, Value>)h.Right).Color = BLACK;
        }

        public override void Delete(Key key)
        {
            throw new NotImplementedException();
        }

    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringST
{
    public class TST<Value>:IStringST<Value>
    {
        private Node root;

        public bool IsEmpty => throw new NotImplementedException();

        public int Size => throw new NotImplementedException();

        public bool Contains(string key)
        {
            throw new NotImplementedException();
        }

        public void Delete(string key)
        {
            throw new NotImplementedException();
        }

        public Value Get(string key)
        {
            var x = Get(root, key, 0);
            if (x == null)
                return default;
            return x.Val;
        }

        private Node Get(Node x, string key, int d)
        {
            if (x == null)
                return null;
            char c = key[d];
            if (c < x.C)
                return Get(x.Left, key, d);
            else if (c > x.C)
                return Get(x.Right, key, d);
            else if (d < key.Length - 1)
                return Get(x.Mid, key, d + 1);
            else
                return x;
        }

        public IEnumerable<string> Keys()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<string> KeysThatMatch(string s)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<string> KeysWithPrefix(string s)
        {
            throw new NotImplementedException();
        }

        public string LongestPrefixOf(string s)
        {
            throw new NotImplementedException();
        }

        public void Put(string key, Value val)
        {
            root = Put(root, key, val, 0);
        }

        private Node Put(Node x, string key, Value val, int d)
        {
            char c = key[d];
            if(x==null)
            {
                x = new Node();
                x.C = c;
            }
            if (c < x.C)
                x.Left = Put(x.Left, key, val, d);
            else if (c > x.C)
                x.Right = Put(x.Right, key, val, d);
            else if (d < key.Length - 1)
                x.Mid = Put(x.Mid, key, val, d + 1);
            else
                x.Val = val;
            return x;
        }

        class Node
        {
            public char C { get; set; }
            public Node Left { get; set; }
            public Node Mid { get; set; }
            public Node Right { get; set; }
            public Value Val { get; set; }
        }
    }
}

using Chapter1;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringST
{
    class TrieST<Value>:IStringST<Value>
    {
        private static int R = 256; //基数
        private Node root;

        public bool IsEmpty => throw new NotImplementedException();

        public int Size => throw new NotImplementedException();

        public bool Contains(string key)
        {
            var x = root;
            if (x == null)
                return false;
            for (int i = 0; i < key.Length; i++)
            {
                char c = key[i];
                x = x.Next[i];
                if (x == null)
                    return false;
            }
            if (x.Val == null)
                return false;
            return true;
        }

        public void Delete(string key)
        {
            root = Delete(root, key, 0);
        }

        //删除一个键和它相关联的值
        private Node Delete(Node x, string key, int d)
        {
            if (x == null)
                return null;
            if (d == key.Length)
                x.Val = default;
            else
            {
                char c = key[d];
                x.Next[c] = Delete(x.Next[c], key, d + 1);
            }
            if (x.Val != null)
                return x;
            for (short c = 0; c < R; c++)
                if (x.Next[c] != null)
                    return x;
            return null;
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
            if (d == key.Length)
                return x;
            char c = key[d]; //找到第d个字符所对应的子单词查找树
            return Get(x.Next[c], key, d + 1);
        }

        public IEnumerable<string> Keys()
        {
            return KeysWithPrefix("");
        }

        public IEnumerable<string> KeysThatMatch(string s)
        {
            var q = new Chapter1.Queue<string>();
            Collect(root, "", s, q);
            return q;
        }

        private void Collect(Node x, string pre, string pat, Chapter1.Queue<string> q)
        {
            int d = pre.Length;
            if (x == null)
                return;
            if (d == pat.Length && x.Val != null)
                q.Enqueue(pre);
            if (d == pat.Length)
                return;

            char next = pat[d];
            for (short c = 0; c < R; c++)
                if (next == '.' || next == Convert.ToChar(c))
                    Collect(x.Next[c], pre + Convert.ToChar(c), pat, q);
        }

        public IEnumerable<string> KeysWithPrefix(string s)
        {
            var q = new Chapter1.Queue<string>();
            Collect(Get(root, s, 0), s, q);
            return q;
        }

        private void Collect(Node node, string s, Chapter1.Queue<string> q)
        {
            if (node == null)
                return;
            if (node.Val != null)
                q.Enqueue(s);
            for (short c = 0; c < R; c++)
                Collect(node.Next[c], s + Convert.ToChar(c), q);
        }

        public string LongestPrefixOf(string s)
        {
            int length = Search(root, s, 0, 0);
            return s.Substring(0, length);
        }

        private int Search(Node x, string s, int d, int length)
        {
            if (x == null)
                return length;
            if (x.Val != null)
                length = d;
            if (d == s.Length)
                return length;
            char c = s[d];
            return Search(x.Next[Convert.ToInt32(c)], s, d + 1, length);
        }

        public void Put(string key, Value val)
        {
            root = Put(root, key, val, 0);
        }

        private Node Put(Node x, string key, Value val, int d)
        {
            //如果key存在于以x为根节点的子单词查找树中，则更新与他相关联的值
            if (x == null)
                x = new Node();
            if(d==key.Length)
            {
                x.Val = val;
                return x;
            }
            char c = key[d];
            x.Next[c] = Put(x.Next[c], key, val, d + 1);
            return x;
        }

        class Node
        {
            public Value Val { get; set; }
            public Node[] Next = new Node[R];
            public Node()
            {

            }
            public Node(Value value)
            {
                this.Val = value;
            }
        }

        
    }
}

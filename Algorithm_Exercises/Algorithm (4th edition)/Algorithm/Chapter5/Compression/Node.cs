using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace Chapter5.Compression
{
    public class Node : IComparable<Node>
    {
        public char Ch { get; set; } //内部节点不会使用该变量
        public readonly int freq; //展开过程不会使用该变量
        public Node Left { get; }
        public Node Right { get; }

        public Node(char ch, int freq, Node left, Node right)
        {
            this.Ch = ch;
            this.freq = freq;
            this.Left = left;
            this.Right = right;
        }

        public bool isLeaf()
        {
            return Left == null && Right == null;
        }

        public int CompareTo([AllowNull] Node other)
        {
            return this.freq - other.freq;
        }
    }
}

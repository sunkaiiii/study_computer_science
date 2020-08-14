using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{

    public class Node<K,V>
    {
        public K Key { get; }
        public V Val { get; set; }
        public Node<K,V> Left { get; set; }
        public Node<K,V> Right { get; set; }
        public int N { get; set; } //以该节点为根的子树中的节点总数
        public Node(K key, V val, int N)
        {
            this.Key = key;
            this.Val = val;
            this.N = N;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    public class RedBlackBSTNode<K,V>:Node<K,V>
    {
        public bool Color { get; set; }

        public RedBlackBSTNode(K key, V val, int n, bool color):base(key,val,n)
        {
            Color = color;
        }
    }
}

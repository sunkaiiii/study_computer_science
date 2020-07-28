using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter1
{
    internal class Node<T>
    {
        public T Item { get; set; }
        public Node<T> Next { get; set; }
    }
}

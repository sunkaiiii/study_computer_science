using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    public class SeparateChainingHashST<Key,Value>:IHashTable<Key,Value>
    {
        public int N { get; private set; } //键值对的总数
        public int M { get; private set; } //散列表的大小
        private SequantialSearchST<Key, Value>[] st;


        public SeparateChainingHashST(int m=997)
        {
            //创建M条链表
            this.M = m;
            st = new SequantialSearchST<Key, Value>[M];
            for (int i = 0; i < M; i++)
                st[i] = new SequantialSearchST<Key, Value>();
        }

        private int Hash(Key key)
        {
            return (int)((key.GetHashCode() & 0x7ffffffff) % M);
        }
        
        public Value Get(Key key)
        {
            return st[Hash(key)].Get(key);
        }

        public void Put(Key key,Value value)
        {
            st[Hash(key)].Put(key, value);
        }

        public void Delete(Key key)
        {
            st[Hash(key)].Delete(key);
        }
    }
}

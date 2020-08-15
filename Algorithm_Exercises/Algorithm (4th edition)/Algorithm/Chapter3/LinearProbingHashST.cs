using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    public class LinearProbingHashST<Key,Value>:IHashTable<Key,Value>
    {
        public int N { get; private set; } = 0;
        private int M { get; set; }
        private Key[] keys;
        private Value[] vals;
        public LinearProbingHashST(int cap=16)
        {
            M = cap;
            keys = new Key[M];
            vals = new Value[M];
        }

        private int Hash(Key key) => (key.GetHashCode() & 0x7fffffff) % M;

        private void Resize() { }

        public void Put(Key key,Value value)
        {
            if (N >= M / 2)
                Resize(2 * M); //将M加倍

            int i;
            for(i=Hash(key);keys[i]!=null;i=(i+1)%M)
                if(keys[i].Equals(key)) //如果已有，更新
                {
                    vals[i] = value;
                    return;
                }
            keys[i] = key;
            vals[i] = value;
            N++;
        }

        public Value  Get(Key key)
        {
            for (int i = Hash(key); keys[i] != null; i = (i + 1) % M)
                if (keys[i].Equals(key))
                    return vals[i];
            return default;
        }

        public void Delete(Key key)
        {
            if (Get(key)==null)
                return;
            int i = Hash(key);
            while (!key.Equals(keys[i]))
                i = (i + 1) % M;
            keys[i] = default;
            vals[i] = default;
            i = (i + 1) % M;
            while(keys[i]!=null)
            {
                Key keyToRedo = keys[i];
                Value valToRedo = vals[i];
                keys[i] = default;
                vals[i] = default;
                N--;
                Put(keyToRedo, valToRedo);
                i = (i + 1) % M;
            }
            N--;
            if (N > 0 && N == M / 8)
                Resize(M / 2);
        }

        private void Resize(int cap)
        {
            LinearProbingHashST<Key, Value> t = new LinearProbingHashST<Key, Value>(cap);
            for (int i = 0; i < M; i++)
                if (keys[i] != null)
                    t.Put(keys[i], vals[i]);
            keys = t.keys;
            vals = t.vals;
            M = t.M;
        }
    }
}

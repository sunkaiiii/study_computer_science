using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    public interface IHashTable<Key,Value>
    {
        void Put(Key key, Value value);
        void Delete(Key key);
        Value Get(Key key);
    }
}

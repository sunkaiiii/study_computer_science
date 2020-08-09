using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    interface ISearchTable<Key,Value>
    {
        void Put(Key key, Value value);
        Value Get(Key key);
        IEnumerable<Key> Keys();
        bool Contains(Key key);
        void Delete(Key key);
        bool IsEmpty { get; }
    }
}

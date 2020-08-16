using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    public interface ISearchTable<Key,Value>
    {
        public int Size { get; }
        void Put(Key key, Value value);
        Value Get(Key key);
        IEnumerable<Key> Keys();
        bool Contains(Key key);
        void Delete(Key key);
        bool IsEmpty { get; }
    }
}

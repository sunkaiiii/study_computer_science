using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter3
{
    interface ISearchTable<Key,Value>
    {
        void Put(Key key, Value value);
        Value Get(Key key);
        void Delete(Key key)
        {
            Put(key, default(Value)); //延迟删除的默认实现
        }
        bool Contains(Key key)
        {
            return Get(key) != null;
        }
        bool IsEmpty { get
            {
                return Size == 0;
            }
        }
        int Size { get; }
        IEnumerable<Key> Keys();
    }
}

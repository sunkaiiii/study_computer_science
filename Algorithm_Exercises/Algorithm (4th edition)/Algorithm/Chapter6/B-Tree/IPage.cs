using System;
using System.Collections.Generic;

namespace Chapter6.BTree
{
    public interface IPage<Key>:IEnumerable<Key>
    {
        void Close(); //关闭页
        void Add(Key key); //将键插入页中
        void Add(IPage<Key> p); //打开p，向这个页中插入一个条目并将p和p中的最小键相关联
        bool IsExternal(); //是否是一个外部页？
        bool Contains(Key key);
        IPage<Key> Next(Key key); //可能含有key的子树
        bool IsFull(); //页是否溢出
        IPage<Key> Split();//将较大的中间键移动到一个新页中
    }
}

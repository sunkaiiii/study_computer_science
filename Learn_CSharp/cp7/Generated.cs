using System;
using System.Collections.Generic;
using System.Text;

namespace cp7
{
    partial class PartialMethodDemo
    {
        public PartialMethodDemo()
        {
            //如果没有任何的分部方法实现了这个method，这个调用信息将会在编译器的时候移除。
            OnConstructorStart();
            Console.WriteLine("Generated constructor");
            OnConstructorEnd();
        }

        partial void OnConstructorStart();
        partial void OnConstructorEnd();
    }
}

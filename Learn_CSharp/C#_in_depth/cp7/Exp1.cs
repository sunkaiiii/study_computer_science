using System;
using System.Collections.Generic;
using System.Text;

namespace cp7
{
    partial class Example<TFirst,TSecond>:IEquatable<string> where TFirst:class //接口和类型约束
    {
        public bool Equals(string other)
        {
            return false;
        }
    }
}

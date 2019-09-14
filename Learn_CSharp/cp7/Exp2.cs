using System;
using System.Collections.Generic;
using System.Text;

namespace cp7
{
   partial class Example<TFirst,TSecond>:EventArgs,IDisposable //指定基类和接口
    {
        public void Dispose() //实现接口
        { }
    }
}

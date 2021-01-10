using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter8
{
    //分部类
    internal sealed partial class Base 
    {
        //分部方法的实现
        partial void OnNameChanging(string value)
        {
            if (string.IsNullOrEmpty(value))
            {
                throw new ArgumentNullException("value");
            }
        }
    }
}

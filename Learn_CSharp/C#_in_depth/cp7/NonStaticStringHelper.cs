using System;
using System.Collections.Generic;
using System.Text;

namespace cp7
{
   
    //C# 2的工具类。
    public static class StaticStringHelper
    {
        public static string Reverse(string input) //所有的方法都是静态的
        {
            char[] chars = input.ToCharArray();
            Array.Reverse(chars);
            return new string(chars);
        }
    }
    //典型的C# 1工具类
    public sealed class NonStaticStringHelper //密封类防止派生
    {
        private NonStaticStringHelper() { } //防止其他代码对其进行实例化

        public static string Reverse(string input) //所有的方法都是静态的
        {
            char[] chars = input.ToCharArray();
            Array.Reverse(chars);
            return new string(chars);
        }
    }
}

using System;
namespace CP10
{
    public static class NullUtil
    {
        //在空引用上调用扩展方法
        public static bool IsNull(this object x)
        {
            return x == null;
        }
    }
}

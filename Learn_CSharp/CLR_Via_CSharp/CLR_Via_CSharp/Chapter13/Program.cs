using System;

namespace Chapter13
{
    class Program
    {
        sealed class SimpleType:IDisposable
        {
            public void Dispose()
            {
                Console.WriteLine("public dispose");
            }

             //创建显示接口方法实现
             void IDisposable.Dispose()
            {
                Console.WriteLine("IDisposable Dispose");
            }
        }
        static void Main(string[] args)
        {
            SimpleType st = new SimpleType();
            st.Dispose();
            IDisposable d = st;
            d.Dispose();
        }
    }
}

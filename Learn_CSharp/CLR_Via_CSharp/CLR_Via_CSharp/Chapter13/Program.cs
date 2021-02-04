using System;
using System.Diagnostics.CodeAnalysis;

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

        //可以实现泛型接口两次
        public sealed class Number : IComparable<Int32>, IComparable<string>
        {
            private int m_val = 5;
            public int CompareTo([AllowNull] int other)
            {
                return m_val.CompareTo(other);
            }

            public int CompareTo([AllowNull] string other)
            {
                return m_val.CompareTo(int.Parse(other));
            }

            //泛型接口的约束
            private static int M<T>(T t)where T: IComparable, IConvertible
            {
                return 0;
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

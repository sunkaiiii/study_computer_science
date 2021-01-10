using System;

namespace Chapter8
{
    class Program
    {
        //internal struct Point
        //{
        //    public Int32 m_x, m_y;
        //    public Point() // 值类型，没有默认的无参构造函数
        //    {
        //        m_x = m_y = 5;
        //    }
        //}
        internal struct Point
        {
            public Int32 m_x, m_y;
            static Point() // 类型构造器
            {
              
            }
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

using System;
using System.Runtime.InteropServices;

namespace Chapter5
{
    //引用类型
    class SomeRef
    {
        public Int32 x;
    }

    //值类型
    struct SomeVal
    {
        public Int32 x;
    }

    //让CLR自动排列字段以增强这个值类型的性能
    [StructLayout(LayoutKind.Auto)]
    struct SomeValType
    {
        private readonly Byte m_b;
        private readonly Int16 m_x;
    }

    //让开发人员显示排列这个值类型的字段
    [StructLayout(LayoutKind.Explicit)]
    struct SomeValType2
    {
        [FieldOffset(0)]
        private readonly Byte m_b;

        [FieldOffset(0)]
        private readonly Int16 m_x;
    }

    internal struct Point:IComparable
    {
        private Int32 m_x, m_y;

        public Point(Int32 x, Int32 y)
        {
            m_x = x;
            m_y = y;
        }

        //重写从ValueType继承的ToString方法
        public override string ToString()
        {
            return String.Format("{0},{1}", m_x.ToString(), m_y.ToString()); //以字符串范围，避免装箱
        }

        //安全的CompareTo方法
        public Int32 CompareTo(Point other)
        {
            return Math.Sign(Math.Sqrt(m_x * m_x + m_y + m_y) - Math.Sqrt(other.m_x * other.m_x + other.m_y * other.m_y));
        }

        //实现接口的CompareTo
        public Int32 CompareTo(Object o)
        {
            return CompareTo((Point)o);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            SomeRef r1 = new SomeRef(); //在堆上分配
            SomeVal v1 = new SomeVal(); //在栈上分配
            r1.x = 5; //提领指针
            v1.x = 5; //在栈上修改

            SomeRef r2 = r1; //只复制了引用
            SomeVal v2 = v1; ;//在栈上分配并复制成员
            r1.x = 8; //r1,r2都会改变
            v1.x = 8; //v1会改变
            Console.WriteLine(r1.x);
            Console.WriteLine(r2.x);
            Console.WriteLine(v1.x);
            Console.WriteLine(v2.x);


            Int32 v = 5;
#if INEFFICIENT
            Console.WriteLine("{0}, {1}, {2}", v, v, v); //会造成3次装箱，浪费内存
#else
            Object o = v; //手动装箱
            Console.WriteLine("{0},{1},{2}", o, o, o); //不发生装箱
#endif


            //在栈上创建两个Point实例
            Point p1 = new Point(10, 10);
            Point p2 = new Point(20, 20);
            //调用ToString()虚方法，不装箱
            Console.WriteLine(p1.ToString());

            //调用CompareTo，不装箱p1
            Console.WriteLine(p1.CompareTo(p2));
            //调用GetType，装箱
            Console.WriteLine(p1.GetType());
            //装箱到C中
            IComparable c = p1;
            Console.WriteLine(c.GetType());
            //调用CompareTo不装箱p1
            Console.WriteLine(p1.CompareTo(o));
            //这里要装箱p2
            Console.WriteLine(c.CompareTo(p2));
            p2 = (Point)c; //拆箱


            uint invalid = unchecked((uint)-1); //不会造成异常
            Byte b = 100;
            b = checked((Byte)(b + 200)); //抛出溢出异常

            checked
            {
                //对内部所有的内容进行检查
            }
        }
    }
}

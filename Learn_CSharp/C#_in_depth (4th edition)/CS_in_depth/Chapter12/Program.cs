using System;

namespace Chapter12
{
    class Program
    {

        //通过元组字面量和分解操作完成构造器赋值的简单示例
        public sealed class Point
        {
            public double X { get; }
            public double Y { get; }
            public Point(double x, double y) => (X, Y) = (x, y);

            //实例分解方法
            public void Deconstruct(out double x, out double y)
            {
                x = X;
                y = Y;
            }

            //也可以这么写
            //public void Deconstruct(out double x, out double y) => (x, y) = (X, Y);
        }

        //C# 7 当中的模式匹配
        class Shape { }
        class Rectangle : Shape { }
        class Circle : Shape { }
        class Triangle : Shape { }
        static double Perimeter(Shape shape)
        {
            switch(shape)
            {
                case null:
                    throw new ArgumentNullException(nameof(shape));
                case Rectangle rect:
                    return 2;
                case Circle circle:
                    return 3;
                case Triangle tri:
                    return 4;
                default:
                    throw new ArgumentNullException(nameof(shape));
            }
        }

        static void Main(string[] args)
        {
            var tuple = (10, "Text");
            //隐式分解
            var (a, b) = tuple;
            //显示分解
            (int c, string d) = tuple;
            int e;
            string f;
            (e, f) = tuple; //分解到现有变量
            Console.WriteLine($"a: {a}; b: {b}");
            Console.WriteLine($"c: {c}; d: {d}");
            Console.WriteLine($"e: {e}; f: {f}");

            Point point = new Point(1.5, 20);
            var (x, y) = point; //分解一个point
            Console.WriteLine($"x = {x}");
            Console.WriteLine($"y = {y}");

            //使用扩展方法分解DateTime
            DateTime now = DateTime.UtcNow;
            var (year, month, day) = now;
            Console.WriteLine(
            $"{year:0000}-{month:00}-{day:00}");
        }
    }
}

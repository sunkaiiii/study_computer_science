using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace StandardLibraries
{
    public static class StdOut
    {
        private static readonly string CHARSET_NAME = "UTF-8";
        private static readonly TextWriter writer = Console.Out;

        public static void Println() => writer.WriteLine();

        public static void Println(object x) => writer.WriteLine(x);

        public static void Println(bool x) => writer.WriteLine(x);

        public static void Println(char x) => writer.WriteLine(x);

        public static void Println(double x) => writer.WriteLine(x);

        public static void Println(float x) => writer.WriteLine(x);

        public static void Println(int x) => writer.WriteLine(x);

        public static void Println(long x) => writer.WriteLine(x);

        public static void Println(short x) => writer.WriteLine(x);

        public static void Println(byte x) => writer.WriteLine(x);

        public static void Print() => writer.Flush();

        public static void Print(object x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(bool x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(char x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(double x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(float x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(int x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print(long x)
        {
            writer.Write(x);
            writer.Flush();
        }
        public static void Print(short x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Print (byte x)
        {
            writer.Write(x);
            writer.Flush();
        }

        public static void Printf(string format, params object[] args)
        {
            writer.WriteLine(format,args);
        }
    }
}

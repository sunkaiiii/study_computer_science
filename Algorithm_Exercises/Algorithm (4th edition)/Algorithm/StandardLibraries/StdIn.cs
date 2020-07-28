using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace StandardLibraries
{
    public static  class StdIn
    {
        private static Scanner scanner = new Scanner(Console.In);

        public static bool IsEmpty()=>!scanner.HasNext();
        

        public static bool HasNextLine()=> scanner.HasNextLine();
        

        public static bool HasNextChar()=>scanner.HasNextChar();
        

        public static string ReadLine()=> scanner.ReadLine();
  

        public static char ReadChar()=> scanner.ReadChar();
        

        public static string ReadAll()=>scanner.ReadAll();
      

        public static int ReadInt() => scanner.ReadInt();

        public static double ReadDouble() => scanner.ReadDouble();

        public static float ReadFloat() => scanner.ReadFloat();

        public static long ReadLong() => scanner.ReadLong();

        public static short ReadShort() => scanner.ReadShort();

        public static bool? ReadBoolean() => scanner.ReadBool();

        public static string ReadString() => scanner.Read();

        public static string[] ReadAllStrings() => scanner.ReadStrings();

        public static string[] ReadAllLines() => scanner.ReadAllLines();

        public static int[] ReadAllInts() => scanner.ReadInts();

        public static long[] ReadAllLongs() => scanner.ReadLongs();

        public static double[] ReadAllDoubles() => scanner.ReadDoubles();

    }
}

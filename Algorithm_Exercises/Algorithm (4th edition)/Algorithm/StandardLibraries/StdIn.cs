using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace StandardLibraries
{
    public sealed class StdIn
    {
        private static readonly string CHARSET_NAME = "UTF-8";
        private static readonly CultureInfo LOCALE = CultureInfo.CurrentCulture;
        private static readonly Regex EMPTY_PATTERN = new Regex("");
        private static readonly Regex EVERYTHING_PATTERN = new Regex("\\A");
        private static Scanner scanner;
        
        public static bool IsEmpty()
        {
            //Console.In.
            return !scanner.HasNext();
        }

        //public static bool HasNextLine()
       // {
            
       // }
    }
}

using System;

namespace Chapter18
{
    //定制属性
    [Serializable]
    [AttributeUsage(AttributeTargets.Enum, Inherited = false)]
    public class FlagsAttribute : System.Attribute
    {

        public FlagsAttribute()
        {

        }
    }
    class Program
    {
        [Flags]
        enum Test
        {

        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

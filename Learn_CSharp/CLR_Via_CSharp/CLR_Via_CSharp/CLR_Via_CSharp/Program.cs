using System;

//强制符合CLS类型
[assembly: CLSCompliant(true)]
namespace Chapter1
{
    public sealed class Program
    {
        //警告，返回类型不符合CLS   
        public UInt32 Abc() => 0;

        //进大小写不同标识符，不符合CLS
        public void abc() { }

        private UInt32 ABC() => 0;
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

using System;

namespace Chapter16
{
    class Program
    {
        static void Main(string[] args)
        {
            //数组协变性引发的后果
            string[] sa = new string[100];
            object[] oa = sa; //协变性
            oa[5] = "Kai"; //性能损失，CLR要对类型进行检查
                           // oa[3] = 3; //抛出异常

            //栈上数组
            StackAllocDemo();
        }

        private static void StackAllocDemo()
        {
            unsafe
            {
                const int width = 20;
                char* pc = stackalloc char[width]; //在栈上分配数组
                string s = "Kai Sun";
                for(int index = 0;index<width;index++)
                {
                    pc[width - index - 1] = (index < s.Length) ? s[index] : '.';
                }
                Console.WriteLine(new string(pc, 0, width));
            }
          
        }
    }
}

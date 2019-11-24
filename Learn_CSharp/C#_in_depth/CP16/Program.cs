using System;
using System.Collections.Generic;

namespace CP16
{
    class Program
    {
        static void Main(string[] args)
        {
            //C# 5当中得到修改的foreach循环中变量捕获的问题
            string[] values = { "x", "y", "z" };
            var actions = new List<Action>();

            foreach(string value in values)
            {
                actions.Add(() => Console.WriteLine(value));
            }

            foreach(var action in actions)
            {
                action(); //会正确的显示x,y,z
            }
        }
    }
}

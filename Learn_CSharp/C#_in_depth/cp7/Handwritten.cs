using System;
using System.Collections.Generic;
using System.Text;

namespace cp7
{
    partial class PartialMethodDemo
    {
        partial void OnConstructorEnd()
        {
            Console.WriteLine("Manual code");
        }
    }
}

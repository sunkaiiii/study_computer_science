using System;
using System.Diagnostics;
using System.Threading.Tasks;

namespace concurrency_in_CSharp_2th_edition
{
    class Program
    {
        async Task DoSomethingAsync()
        {
            int val = 13;
            await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false); //修改上下文切换的默认行为
            val *= 2;
            await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);

            Trace.WriteLine(val);
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            new Program().DoSomethingAsync().ConfigureAwait(false);
        }
    }
}

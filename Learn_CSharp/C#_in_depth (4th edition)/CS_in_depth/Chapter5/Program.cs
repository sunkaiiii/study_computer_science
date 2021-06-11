using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace Chapter5
{
    class Program
    {
        static readonly HttpClient client = new HttpClient();

        static async Task<int> GetPageLengthAsync(string url)
        {
            Task<string> fetchTextTask = client.GetStringAsync(url);
            int length = (await fetchTextTask).Length;
            return length;
        }

        static void PrintPageLength()
        {
            Task<int> lengthTask = GetPageLengthAsync("https://www.google.com");
            Console.WriteLine(lengthTask.Result);
        }

        //在async方法中使用非安全的代码
        static async Task DelayWithResultOfUnsafeCode(string text)
        {
            int total = 0;
            unsafe
            {
                fixed (char* textPointer = text)
                {
                    char* p = textPointer;
                    while (*p != 0)
                    {
                        total += *p;
                        p++;
                    }
                }
            }
            Console.WriteLine("Delaying for " + total + "ms");
            await Task.Delay(total);
            Console.WriteLine("Delay complete");
        }

        //await完成和未完成的task
        static async Task DemoCompletedAsync()
        {
            Console.WriteLine("Before first await");
            await Task.FromResult(10);
            Console.WriteLine("Between awaits");
            await Task.Delay(1000);
            Console.WriteLine("After second await");
        }

        //C# 7.1 异步main方法
        static async Task Main(string[] args)
        {
            var task = DelayWithResultOfUnsafeCode("123");
            PrintPageLength();
            await task;

            task = DemoCompletedAsync();
            Console.WriteLine("Method returned");
            await task;
            Console.WriteLine("Task completed");
        }
    }
}

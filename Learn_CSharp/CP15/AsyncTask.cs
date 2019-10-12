using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Linq;

namespace CP15
{
    class AsyncTask
    {
        public async void DisplayWebSite()
        {
            using(HttpClient client=new HttpClient())
            {
                string text = await client.GetStringAsync("http://csharpindepth.com");
                Console.WriteLine(text);
            }
        }

        public static async Task<int> GetPageLengthAsync(string url)
        {
            using(HttpClient client=new HttpClient())
            {
                Task<string> fetchTextTask = client.GetStringAsync(url);
                int length = (await fetchTextTask).Length;
                return length;
            }
        }

        public async Task<string> FetchFirstSuccessfulAsync(IEnumerable<string> urls)
        {
            foreach(string url in urls)
            {
                try
                {
                    using (var client = new HttpClient())
                    {
                        return await client.GetStringAsync(url);
                    }
                }catch(WebException exception)
                {
                    Console.WriteLine("there is an error");
                }
            }
            throw new WebException("No URLs succeeded");
        }

        //以熟悉的方式处理异步的异常
        public static async Task MainAsync()
        {
            Task<string> task = ReadFileAsync("garbage file");
            try
            {
                string text = await task;
                Console.WriteLine("File contents:{0}", text);
            }catch(IOException e)
            {
                Console.WriteLine("Caught IOException: {0}", e.Message);
            }
        }

        static async Task<string> ReadFileAsync(string filename)
        {
            using(var reader=File.OpenText(filename))
            {
                return await reader.ReadToEndAsync();
            }
        }

        //通过抛出OperationCancledException来创建一个取消任务
        public static async Task ThrowCancellationException()
        {
            throw new OperationCanceledException();
        }

        //通过一个取消的延迟操作来取消异步方法
        public static async Task DelayFor30Seconds(CancellationToken token)
        {
            Console.WriteLine("Waiting for 30 seconds...");
            await Task.Delay(TimeSpan.FromSeconds(30), token);
        }

        public static async Task<int> ShowPageLengthsAsync(params string[] urls)
        {
            var tasks = urls.Select(async url =>
              {
                  using (var client = new HttpClient())
                  {
                      return await client.GetStringAsync(url);
                  }
              }).ToList();
            int total = 0;
            foreach(var task in tasks.InCompletionOrder())
            {
                string page = await task;
                Console.WriteLine("Got Page length: {0}", page.Length);
                total += page.Length;
            }
            return total;
        }
    }
}

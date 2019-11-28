using System;
using System.Net;
using System.Net.Http;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading.Tasks;
using System.Threading.Tasks.Dataflow;

namespace CP7
{
    static class Program
    {
        public static Task<string> DownloadStringTaskAsync(this WebClient client, Uri address)
        {
            var tcs = new TaskCompletionSource<string>();
            //这个时间处理程序完成Task对象，并自行注销
            DownloadStringCompletedEventHandler handler = null;
            handler = (_, e) =>
            {
                client.DownloadStringCompleted -= handler;
                if (e.Cancelled)
                    tcs.TrySetCanceled();
                else if (e.Error != null)
                    tcs.TrySetException(e.Error);
                else
                    tcs.TrySetResult(e.Result);
            };
            //登记事件，然后开始操作
            client.DownloadStringCompleted += handler;
            client.DownloadStringAsync(address);
            return tcs.Task;
        }

        //定义了一个扩展方法，发送一个HTTP请求并获取响应
        public static Task<WebResponse> GetResponse(this WebRequest client)
        {
            return Task<WebResponse>.Factory.FromAsync(client.BeginGetResponse, client.EndGetResponse, null);
        }

        //非标准类型的异步编程方法，使用TaskCompletionSource<T>进行封装
        public interface IMyAsyncHttpService
        {
            void DownloadString(Uri address, Action<string, Exception> callback);
        }
        public static Task<string> DownloadStringAsync(this IMyAsyncHttpService httpService, Uri address)
        {
            var tcs = new TaskCompletionSource<string>();
            httpService.DownloadString(address, (result, exception) =>
            {
                if (exception != null)
                    tcs.TrySetException(exception);
                else
                    tcs.TrySetResult(result);
            });
            return tcs.Task;
        }

        static void Main(string[] args)
        {
            //使用Rx Observable对象封装async代码
            //将Task<T>转换为IObservable<T>
            var client = new HttpClient();
            IObservable<HttpResponseMessage> response = client.GetAsync("http://kworb.net/pop/").ToObservable();
            //另一种方法是调用StartAsync
            IObservable<HttpResponseMessage> response2 = Observable.StartAsync(token => client.GetAsync("http://kworb.net/pop/",token));
            //这两个方法都会立即启动异步操作，如果想要其接受订阅后启动，可使用FromAsync
            IObservable<HttpResponseMessage> response3 = Observable.FromAsync(token => client.GetAsync("http://kworb.net/pop/", token));


            //Rx Observable对象和数据流网络
            var buffer = new BufferBlock<int>();
            IObservable<int> integers = buffer.AsObservable(); //创建一个缓冲块到Observable对象的接口
            integers.Subscribe(data => Console.WriteLine(data), ex => Console.WriteLine(ex), () => Console.WriteLine("done"));
            //如果使用一个网格并把它作为观察流的目的，情况会稍微复杂一点。
            //ticks->display->done
            IObservable<DateTimeOffset> ticks = Observable.Interval(TimeSpan.FromSeconds(1)).Timestamp().Select(x => x.Timestamp).Take(5);
            var display = new ActionBlock<DateTimeOffset>(x => Console.WriteLine(x));
            ticks.Subscribe(display.AsObserver());
            try
            {
                display.Completion.Wait();
                Console.WriteLine("Done.");
            }catch(Exception ex)
            {
                Console.WriteLine(ex);
            }
        }
    }
}

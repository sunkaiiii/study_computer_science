using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace Chapter8
{
    public static class Extensions
    {
        // 异步包装“已完成”事件和异步方法
        public static Task<string> DownloadStringTaskAsync(this WebClient client, Uri address)
        {
            var tcs = new TaskCompletionSource<string>();
            // 事件处理程序会完成任务，然后自行注销
            DownloadStringCompletedEventHandler handler = null;
            handler = (_, e) =>
            {
                client.DownloadStringCompleted -= handler;
                if (e.Cancelled)
                {
                    tcs.TrySetCanceled();
                }
                else if (e.Error != null)
                {
                    tcs.TrySetException(e.Error);
                }
                else
                {
                    tcs.TrySetResult(e.Result);
                }
            };
            // 为事件注册，然后开始操作
            client.DownloadStringCompleted += handler;
            client.DownloadString(address);
            return tcs.Task;
        }

        // 异步包装Begin方法和End方法
        public static Task<WebResponse> GetResponseAsync(this WebRequest client)
        {
            return Task<WebResponse>.Factory.FromAsync(client.BeginGetResponse, client.EndGetResponse, null);
        }

        // 异步包装任意对象
        public interface IMyAsyncHttpService
        {
            void DownloadString(Uri address, Action<string, Exception> callback);
        }

        public static Task<string> DownloadStringAsync2(this IMyAsyncHttpService httpService, Uri address)
        {
            var tcs = new TaskCompletionSource<string>();
            httpService.DownloadString(address, (result, exception) =>
            {
                if (exception != null)
                {
                    tcs.TrySetException(exception);
                }
                else
                {
                    tcs.TrySetResult(result);
                }
            });
            return tcs.Task;
        }


        // 用于异步代码的System.Reactive可观察包装器 
        public static IObservable<HttpResponseMessage> GetPage(HttpClient client)
        {
            Task<HttpResponseMessage> task = client.GetAsync("www.google.com");
            return task.ToObservable();
        }

        // 支持取消的异步
        public static IObservable<HttpResponseMessage> GetPage2(HttpClient client)
        {
            return Observable.StartAsync(token => client.GetAsync("www.google.com", token));
        }

        // 创建”冷“的可观察对象
        public static IObservable<HttpResponseMessage> GetPage3(HttpClient client)
        {
            return Observable.FromAsync(token => client.GetAsync("www.google.com", token));
        }

        //  在源流中的每个事件到来时，可以使用特殊的SelectMany重载来为他们启动异步操作
        public static IObservable<HttpResponseMessage> GetPage4(IObservable<string> urls, HttpClient client)
        {
            return urls.SelectMany((url, token) => client.GetAsync(url, token));
        }

        // System.Reactive可观察对象转换为异步流
        public static void ReactiveToAsync1()
        {
            // 可能会有内存消耗问题
            IObservable<long> observable = Observable.Interval(TimeSpan.FromSeconds(1));
            IAsyncEnumerable<long> enumerable = observable.ToAsyncEnumerable();
        }

        // 将通道用作未经限制的生产者队列，但依然会有内存问题
        public static async IAsyncEnumerable<T> ToAsyncEnumerable<T>(
            this IObservable<T> observable)
        {
            Channel<T> buffer = Channel.CreateUnbounded<T>();
            using (observable.Subscribe(value => buffer.Writer.TryWrite(value),
                error => buffer.Writer.Complete(error),
                () => buffer.Writer.Complete()))
            {
                await foreach (T item in buffer.Reader.ReadAllAsync())
                    yield return item;
            }
        }

        // 使用受限制的队列可以规避内存问题
        public static async IAsyncEnumerable<T> ToAsyncEnumerable<T>(
                this IObservable<T> observable, int bufferSize)
        {
            var bufferOptions = new BoundedChannelOptions(bufferSize)
            {
                FullMode = BoundedChannelFullMode.DropOldest //丢弃最早的项目
            };
            Channel<T> buffer = Channel.CreateBounded<T>(bufferOptions);
            using(observable.Subscribe(value=>buffer.Writer.TryWrite(value),
                error=>buffer.Writer.Complete(error),
                () => buffer.Writer.Complete()))
            {
                await foreach(T item in buffer.Reader.ReadAllAsync())
                {
                    yield return item;
                }
            }
        }
    }
}

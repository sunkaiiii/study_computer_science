using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chapter7
{
    class TestedClass
    {
        public async Task<int> GetResultAsyn()
        {
            await Task.Delay(400);
            return 1;
        }

        public IObservable<string> GetString(string url)
        {
            if (url == "Exception")
                return Observable.Throw<string>(new HttpRequestException());
            return Observable.Return("stub");
        }

        public async Task ThrowExceptionAsync()
        {
            await Task.FromException(new DivideByZeroException());
        }

        public IObservable<string> GetStringWithDelay(string url, IScheduler scheduler)
        {
            return Observable.Return("stub").Delay(TimeSpan.FromSeconds(0.5), scheduler);
        }
        
        public IObservable<string> GetStringWithTimeout(string url, IScheduler scheduler = null)
        {
            return GetStringWithDelay(url, scheduler ?? Scheduler.Default).Timeout(TimeSpan.FromSeconds(1), scheduler ?? Scheduler.Default);
        }
        
    }

}

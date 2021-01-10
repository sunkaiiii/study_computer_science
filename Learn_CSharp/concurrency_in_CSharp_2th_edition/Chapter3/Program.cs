using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;

namespace Chapter3
{
    class Program
    {
        //最简单的方式创建异步流
        async IAsyncEnumerable<int> GetValuesAsync([EnumeratorCancellation] CancellationToken token = default)
        {
            await Task.Delay(1000,token);
            yield return 10;
            await Task.Delay(1000,token);
            yield return 13;
        }

        async Task TryAsyncTask()
        {
            var value = GetValuesAsync().WhereAwait(async value =>  //可以对异步流实行LINQ
            {
                await Task.Delay(10);
                return value % 2 == 0;
            }).CountAsync(value => value - 1 > 0);

            await foreach (int i in GetValuesAsync().ConfigureAwait(false)) 
            {
                Console.WriteLine(i);
            }
            Console.WriteLine(await value);

            //取消异步流
            using var cts = new CancellationTokenSource(500);
            var token = cts.Token;
            await foreach(int result in GetValuesAsync().WithCancellation(token)) 
            {
                Console.WriteLine(result);
            }
        }
        static void Main(string[] args)
        {
            new Program().TryAsyncTask().Wait();
        }
    }
}

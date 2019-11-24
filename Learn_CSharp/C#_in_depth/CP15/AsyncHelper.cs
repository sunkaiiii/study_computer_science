using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Linq;
using System.Threading;

namespace CP15
{
    static class AsyncHelper
    {
        //按完成顺序将任务序列转换到新的集合
        public static IEnumerable<Task<T>> InCompletionOrder<T>(this IEnumerable<Task<T>> source)
        {
            var inputs = source.ToList();
            var boxes = inputs.Select(x => new TaskCompletionSource<T>()).ToList();
            int currentIndex = -1;
            foreach(var task in inputs)
            {
                task.ContinueWith(completed =>
                {
                    var nextbox = boxes[Interlocked.Increment(ref currentIndex)];
                }, TaskContinuationOptions.ExecuteSynchronously);
            }
            return boxes.Select(box => box.Task);
        }


    }
}

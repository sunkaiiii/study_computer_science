using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks.Dataflow;

namespace Chapter8
{
    public static class DataflowExtensions
    {
        public static bool TryReceiveItem<T>(this ISourceBlock<T> block, out T value)
        {
            if (block is IReceivableSourceBlock<T> receiveSourceBlock)
                return receiveSourceBlock.TryReceive(out value);

            try
            {
                value = block.Receive(TimeSpan.Zero);
                return true;
            }catch(TimeoutException)
            {
                value = default;
                return false;
            }
            catch(InvalidOperationException)
            {
                value = default;
                return false;
            }
        }

        public static async IAsyncEnumerable<T> ReceiveAllAsync<T>(this ISourceBlock<T> block, [EnumeratorCancellation]CancellationToken cancellation=default)
        {
            while(await block.OutputAvailableAsync(cancellation).ConfigureAwait(false))
            {
                while(block.TryReceiveItem(out var value))
                {
                    yield return value;
                }
            }
        }
    }
}

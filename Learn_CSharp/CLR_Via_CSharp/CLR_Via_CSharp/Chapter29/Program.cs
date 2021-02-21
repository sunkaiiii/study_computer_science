using System;
using System.Threading;

namespace Chapter29
{
    class Program
    {
        //要修复上述问题，应该加入voliate关键字
        private static bool s_stopWorker = false;

        //在程序进行优化之后，程序的工作方式可能会和想象有出入
        static void Main(string[] args)
        {
            Console.WriteLine("Main: letting worker run for 5 seconds");
            Thread t = new Thread(Worker);
            t.Start();
            Thread.Sleep(5000);
            s_stopWorker = true;
            Console.WriteLine("Main: wating for worker to stop");
            t.Join();
        }

        private static void Worker(object o)
        {
            int x = 0;
            //当在Release环境下，线程发现整个函数内都没有对s_stopWorker进行修改
            //于是，while循环将会被优化成当前s_stopWorker的值，可能是false也可能是true
            //如果为false，则立即返回0
            //为true，则线程进入永久的循环当中
            while(!s_stopWorker)
            {
                x++;
            }
            Console.Write("Worker: stopped when x={0}", x);
        }


        //实现简单自旋锁
        //在多线程处理中，它意味着让一个线程暂时原地打断，避免它跑去与另一个线程竞争资源
        internal struct SimpleSpinLock
        {
            private int m_resourceInUse;

            public void Enter()
            {
                while(true)
                {
                    //总是将资源设为“正在使用”(1)
                    //只有从“未使用”编程“正在使用，才会返回”
                    if (Interlocked.Exchange(ref m_resourceInUse, 1) == 0) //这个目前的问题，就是会一直占用CPU时间，好在FCL提供了SpinWait的黑科技
                        return;
                }
            }

            public void Leave()
            {
                //将资源标记位“未使用”
                Volatile.Write(ref m_resourceInUse, 0);
            }
        }

        //使用乐观锁的原子Maximum方法
        public static int Maximum(ref int target, int value)
        {
            int currentVal = target, startVal, desiredVal;
            //不要在循环中访问目标(target),除非是想要改变它时另一个线程也在动它
            do
            {
                startVal = currentVal;

                desiredVal = Math.Max(startVal, value);

                //线程在这里可能被抢占，所以这行代码不是原子性的
                if (target == startVal)
                {
                    target = desiredVal;
                }

                //而应该使用以下原子性的CompareExchange方法
                currentVal = Interlocked.CompareExchange(ref target, desiredVal, startVal);
            } while (startVal != currentVal);

            return desiredVal;
        }

        //通过自动重置事件轻松创建线程同步锁
        //event每一个调用都强迫调用线程从托管代码转换为内核代码
        //这在竞争比较小的时候速度要慢于自旋锁
        //但是存在竞争时，则有性能优势
        internal sealed class SimpleWait : IDisposable
        {
            private readonly AutoResetEvent m_available;

            public SimpleWait()
            {
                m_available = new AutoResetEvent(true);
            }

            public void Enter()
            {
                m_available.WaitOne();
            }

            public void Leave()
            {
                m_available.Set();
            }

            public void Dispose()
            {
                m_available.Dispose();
            }
        }

        //通过信号量也可以实现类似的效果
        internal sealed class SimpleWaitLock:IDisposable
        {
            private Semaphore m_available;

            public SimpleWaitLock(int maxConcurrent)
            {
                m_available = new Semaphore(maxConcurrent, maxConcurrent);
            }

            public void Enter()
            {
                m_available.WaitOne();
            }

            public void Leave()
            {
                m_available.Release(1);
            }

            public void Dispose()
            {
                m_available.Close();
            }
        }
    }
}

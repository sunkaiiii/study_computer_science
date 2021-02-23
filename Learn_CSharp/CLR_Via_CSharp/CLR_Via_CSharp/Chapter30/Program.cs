using System;
using System.Threading;

namespace Chapter30
{
    class Program
    {
        //混合线程同步的例子
        internal sealed class SimpleHybridLock : IDisposable
        {
            //基于用户模式构造
            private int m_waiters = 0;
            //基于内核模式构造
            private AutoResetEvent m_waiterLock = new AutoResetEvent(false);

            public void Enter()
            {
                //指出这个线程想要获得锁
                if (Interlocked.Increment(ref m_waiters)==1)
                    return; //锁可以直接使用无需竞争

                //另一个线程拥有锁，发生竞争，这里会进入内核态，对性能有较大影响
                m_waiterLock.WaitOne();
            }

            public void Leave()
            {
                if (Interlocked.Decrement(ref m_waiters) == 0)
                    return;
                m_waiterLock.Set(); //有其他性能等待，唤醒，对性能有影响
            }

            public void Dispose()
            {
                m_waiterLock.Dispose();
            }

        }

        //自旋、线程所有权和递归
        internal sealed class AnotherHybridLock:IDisposable
        {
            private int m_waiters = 0;
            private AutoResetEvent m_waiterLock = new AutoResetEvent(false);

            //这个字符控制自旋
            private int m_spinCount = 4000; //随意选择一个计数

            //字段指出哪个线程拥有锁，以及拥有了它多少次
            private int m_owningThreadId = 0, m_recursion = 0;

            public void Enter()
            {
                int threadId = Thread.CurrentThread.ManagedThreadId;
                if(threadId==m_owningThreadId)
                {
                    m_recursion++;
                    return;
                }

                //调用线程不拥有锁，尝试获取
                SpinWait spinWait = new SpinWait();
                for (int spinCount = 0; spinCount < m_spinCount; spinCount++)
                {
                    //如果锁可以自由使用了，这个线程就获得它，设置一些状态并返回
                    if (Interlocked.CompareExchange(ref m_waiters, 1, 0) == 0)
                        goto GotLock;
                    //自旋，给其他线程运行的机会，希望锁会释放
                    spinWait.SpinOnce();
                }
                //自旋结束，锁仍未获得，再试一次
                if(Interlocked.Increment(ref m_waiters)>1)
                {
                    //仍然是竟态条件，线程必须阻塞
                    m_waiterLock.WaitOne();
                }
            GotLock:
                m_owningThreadId = threadId;
                m_recursion = 1;
            }

            public void Leave()
            {
                //如果调用线程不拥有锁，说明存在bug
                int threadId = Thread.CurrentThread.ManagedThreadId;
                if (threadId != m_owningThreadId)
                    throw new SynchronizationLockException("Lock not owned by calling thread");

                //递减递归计数，如果这个线程仍然拥有锁，直接返回
                if (--m_recursion > 0)
                    return;
                m_owningThreadId = 0;
                if (Interlocked.Decrement(ref m_waiters) == 0)
                    return;

                m_waiterLock.Set();
            }
        }

        //Lazy类内部实现单例的方式
        internal sealed class Singleton
        {
            private static Singleton s_value = null;

            private Singleton() { }

            public static Singleton GetSingleton()
            {
                if (s_value != null)
                    return s_value;

                Singleton temp = new Singleton();
                Interlocked.CompareExchange(ref s_value, temp, null);

                //如果竞争失败，temp会被垃圾回收
                return s_value;
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}

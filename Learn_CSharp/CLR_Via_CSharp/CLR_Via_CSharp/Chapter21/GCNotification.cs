using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Chapter21
{
    public static class GCNotification
    {
        private static Action<int> s_gcDone = null; // 事件的字段

        public static event Action<int> GCDone
        {
            add
            {
                //如果之前没有登记的委托，就开始报告通知
                if (s_gcDone == null)
                {
                    new GenObject(0);
                    new GenObject(2);
                    s_gcDone += value;
                }
            }
            remove
            {
                s_gcDone = null;
            }
        }

        private sealed class GenObject
        {
            private int m_generation;
            public GenObject(int generation)
            {
                m_generation = generation;
            }
            ~GenObject()
            {
                //如果对象在我们希望的代中，则通知
                if (GC.GetGeneration(this) >= m_generation)
                {
                    Action<int> temp = Volatile.Read(ref s_gcDone);
                    if (temp != null)
                    {
                        temp(m_generation);
                    }

                    //如果至少还有一个已登记的委托，而且AppDomain并非正在卸载
                    //而且进程并非正在关闭，就继续报告通知
                    if ((s_gcDone != null) && !AppDomain.CurrentDomain.IsFinalizingForUnload() && !Environment.HasShutdownStarted)
                    {
                        //对于第0代，创建一个新对象，对于第2代，复活对象
                        if (m_generation == 0)
                            new GenObject(0);
                        else
                            GC.ReRegisterForFinalize(this);
                    }
                }
            }
        }
    }
}

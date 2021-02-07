using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace Chapter21
{
    public abstract class SafeHandle:CriticalFinalizerObject,IDisposable
    {
        //这是本机资源的句柄
        protected IntPtr handle;
        private bool ownsHandle;

        protected SafeHandle(IntPtr invalidHandleValue, bool ownsHandle)
        {
            this.handle = invalidHandleValue;
            this.ownsHandle = ownsHandle;
        }

        protected void SetHandle(IntPtr handle)
        {
            this.handle = handle;
        }

        public void Dispose()
        {
            Dispose(true);
        }

        protected virtual void Dispose(bool disposing)
        {
            //默认的实现，不建议重写这个方法
            if (handle == null)
                return;
            if (!ownsHandle)
                return;
            bool result = ReleaseHandle();
            GC.SuppressFinalize(this); //阻止调用finalise方法
            IsInvalid = false;
            if (result)
                return;
            
        }

        ~SafeHandle() { Dispose(false); } //默认的实现，不建议重写这个方法

        protected abstract bool ReleaseHandle();

        public void SetHandleAsInvalid()
        {
            GC.SuppressFinalize(this);
        }
        public bool IsClosed
        {
            get
            {
                return IsInvalid;
            }
        }

        public abstract bool IsInvalid { get; set; } //派生类要重写这个属性
    }
}

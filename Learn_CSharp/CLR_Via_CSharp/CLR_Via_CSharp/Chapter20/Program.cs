using System;
using System.Runtime.Serialization;
using System.Security.Permissions;

namespace Chapter20
{
    //定义自己的异常类
    [Serializable]
    public sealed class Exception<TExceptionArgs>:Exception, ISerializable where TExceptionArgs:ExceptionArgs
    {
        private const string c_args = "Args"; //用于序列化
        private readonly TExceptionArgs m_args;

        public TExceptionArgs Args { get { return m_args; } }

        public Exception(string message = null, Exception innerException = null):this(null,message,innerException)
        {

        }
        public Exception(TExceptionArgs args, string message =null,Exception innerException=null):base(message,innerException)
        {
            m_args = args;
        }

        //这个构造器用于反序列化，由于类是密封的，所以构造器是私有的
        //如果这个类不是密封的，构造器应该是protected
        [SecurityPermission(SecurityAction.LinkDemand,Flags = SecurityPermissionFlag.SerializationFormatter)]
        private Exception(SerializationInfo info, StreamingContext context):base(info,context)
        {
            info.AddValue(c_args, m_args);
            base.GetObjectData(info, context);
        }

        public override string Message
        {
            get
            {
                string baseMsg = base.Message;
                return (m_args == null) ? baseMsg : baseMsg + " (" + m_args.Message + ") ";
            }
        }

        public override bool Equals(object obj)
        {
            Exception<TExceptionArgs> other = obj as Exception<TExceptionArgs>;
            if (other == null)
                return false;
            return Object.Equals(m_args, other.m_args) && base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }

    [Serializable]
    public abstract class ExceptionArgs
    {
        public virtual string Message { get { return String.Empty; } }
    }

    //在这个基础上定义其他类就很简单了
    [Serializable]
    public sealed class DiskFullExceptionArgs : ExceptionArgs
    {
        private readonly string m_diskpath;
        public DiskFullExceptionArgs(string diskPath)
        {
            m_diskpath = diskPath;
        }

        public override string Message => m_diskpath == null ? base.Message : "DiskPath=" + m_diskpath;
    }
    class Program
    {
        static void Main(string[] args)
        {
            //测试异常
            try
            {
                throw new Exception<DiskFullExceptionArgs>(new DiskFullExceptionArgs(@"C:\"), "The disk is full");
            }catch(Exception<DiskFullExceptionArgs> e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}

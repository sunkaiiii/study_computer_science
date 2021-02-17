using System;
using System.Reflection;
using System.Runtime.Remoting;
using System.Threading;

namespace Chapter22
{
    class Program
    {
        //AppDomain没有在.NET Core当中实现，需要使用.NET Framework
        private static void Marshalling()
        {
            //获取AppDomain引用
            AppDomain adCallingThreadDomain = Thread.GetDomain();

            //每个AppDomain都分配了字符串名称
            string callingDomainName = adCallingThreadDomain.FriendlyName;
            Console.WriteLine("Defaul AppDomain friendly name = {0}", callingDomainName);

            //获取包含了Main的方法集
            string exeAssembly = Assembly.GetEntryAssembly().FullName;
            Console.WriteLine("Main assembly={0}", exeAssembly);

            AppDomain ad2 = null;
            //使用Marshal-by-Reference进行通信
            Console.WriteLine("{0} Demo #1", Environment.NewLine);

            //新建一个AppDomain，从当前的继承安全性和配置
            ad2 = AppDomain.CreateDomain("AD #2",null,null);
            MarshalByRefType mbrt = null;

            //将程序集加载到新的AppDomain当中，构造一个对象，把他封装会原来的AppDomain（实际会得到到一个代理引用）
            mbrt = (MarshalByRefType)ad2.CreateInstanceAndUnwrap(exeAssembly, "MarshalByRefType");
            Console.WriteLine("Type={0}", mbrt.GetType()); //CLR在类型上撒谎了
            //证明得到的是一个代理对象的引用
            Console.WriteLine("Is proxy={0}", RemotingServices.IsTransparentProxy(mbrt));

            //看起来像是再MarshalByRefType上调用方法
            //实际是在代理类型上调用方法
            mbrt.SomeMethod();

            //卸载
            AppDomain.Unload(ad2);

            //mbrt引用一个有效的代理对象，代理对象引用一个无效的AppDomain
            try
            {
                mbrt.SomeMethod();
                Console.WriteLine("Successful calling");
            }
            catch (AppDomainUnloadedException)
            {
                Console.WriteLine("Failed call");
            }


            //DEMO2: 使用Marshal-by-value进行跨AppDomain通信
            Console.WriteLine("{0} Demo #2", Environment.NewLine);

            ad2 = AppDomain.CreateDomain("AD #2", null, null);
            mbrt = (MarshalByRefType)ad2.CreateInstanceAndUnwrap(exeAssembly, "MarshalByRefType");
            //对象的方法返回对象的副本，按值封送
            MarshalByValType mbvt = mbrt.MethodWithReturn();
            //证明得到的不是一个代理对象的引用
            Console.WriteLine("Is proxy={0}", RemotingServices.IsTransparentProxy(mbrt));
            Console.WriteLine("Returned object created ", mbvt.ToString());
            //卸载
            AppDomain.Unload(ad2);
            //mbvt是值，卸载AppDomain没有影响
            try
            {
                mbrt.SomeMethod();
                Console.WriteLine("Successful calling");
            }
            catch (AppDomainUnloadedException)
            {
                Console.WriteLine("Failed call");
            }

            //Demo 3: 使用不可封送的类型跨AppDomain通信
            ad2 = AppDomain.CreateDomain("AD #2", null, null);
            mbrt = (MarshalByRefType)ad2.CreateInstanceAndUnwrap(exeAssembly, "MarshalByRefType");
            //对象的方法返回一个不可封送的对象，抛出异常
            NonMarshalableType nmt = mbrt.MethodArgAndReturn(callingDomainName);
        }

        //该实例可跨越AppDomain的边界“按引用封送”
        public sealed class MarshalByRefType : MarshalByRefObject
        {
            public MarshalByRefType()
            {
                Console.WriteLine("{0} ctor running in {1}", this.GetType().ToString(), Thread.GetDomain().FriendlyName);
            }

            public void SomeMethod()
            {
                Console.WriteLine("Executing in " + Thread.GetDomain().FriendlyName);
            }

            public MarshalByValType MethodWithReturn()
            {
                Console.WriteLine("Executing in " + Thread.GetDomain().FriendlyName);
                return new MarshalByValType();
            }

            public NonMarshalableType MethodArgAndReturn(string callingDomainName)
            {
                Console.WriteLine("calling from '{0}' to '{1}'.", callingDomainName, Thread.GetDomain().FriendlyName);
                return new NonMarshalableType();
            }
        }

        //该实例可以跨过AppDomain的边界“按值封送”
        [Serializable]
        public sealed class MarshalByValType : Object
        {
            private DateTime m_creationTime = DateTime.Now; //Datetime 是可序列化的
            public MarshalByValType()
            {
                Console.WriteLine("{0} ctor running in {1}, Created on {2:D}", this.GetType().ToString(), Thread.GetDomain().FriendlyName, m_creationTime);
            }

            public override string ToString()
            {
                return m_creationTime.ToLongDateString();
            }
        }

        //该类的实例不能跨AppDomain传递
        //[Serializable]
        public sealed class NonMarshalableType : Object
        {
            public NonMarshalableType()
            {
                Console.WriteLine("Executing in " + Thread.GetDomain().FriendlyName);
            }
        }
        static void Main(string[] args)
        {
            Marshalling();
        }
    }
}

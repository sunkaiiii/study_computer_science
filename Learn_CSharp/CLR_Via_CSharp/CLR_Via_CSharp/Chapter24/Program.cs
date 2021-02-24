using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Security.Permissions;

namespace Chapter24
{
    class Program
    {

        //可以被序列化的类
        [Serializable]
        class Circle
        {
            private double m_radius;

            [NonSerialized]
            private double m_area;

            public Circle(double radius)
            {
                m_radius = radius;
                m_area = Math.PI * m_radius * m_radius;
            }

            [OnDeserialized]
            private void OnDeserialized(StreamingContext context)
            {
                m_area = Math.PI * m_radius * m_radius;
            }
        }

        [Serializable]
        public class MyType
        {
            int x, y;[NonSerialized] int sum;
            public MyType(int x, int y)
            {
                this.x = x;
                this.y = y;
                this.sum = x + y;
            }

            [OnDeserializing]
            private void OnDeserializing(StreamingContext context)
            {
                //可以为字段设置默认值
            }

            [OnDeserialized]
            private void OnDeserialized(StreamingContext context)
            {
                //可以根据字段值初始化状态

                sum = x + y;
            }

            [OnSerializing]
            private void OnSerializing(StreamingContext context)
            {
                //在序列化前，修改任何需要修改的状态
            }

            [OnSerialized]
            private void OnSerialized(StreamingContext context)
            {
                //在序列化后，恢复任何需要恢复的状态
            }
        }

        //实现ISerializable但是基类没有实现的情况
        [Serializable]
        internal class Base
        {
            protected string m_name = "Jeff";
            public Base()
            {

            }
        }
        [Serializable]
        internal class Derived : Base, ISerializable
        {
            private DateTime m_date = DateTime.Now;
            public Derived()
            {

            }

            //如果此构造器不存在，就会引发一场
            //如果此类不是密封类，这个构造器应该是protected的
            private Derived(SerializationInfo info, StreamingContext context)
            {
                //为基类获取可序列化的成员集合
                Type baseType = this.GetType().BaseType;
                MemberInfo[] mi = FormatterServices.GetSerializableMembers(baseType, context);
                for (int i = 0; i < mi.Length; i++)
                {
                    FieldInfo fi = (FieldInfo)mi[i];
                    fi.SetValue(this, info.GetValue(baseType.FullName + "+" + fi.Name, fi.FieldType));
                }
                //反序列化为这个类序列化值
                m_date = info.GetDateTime("Date");
            }

            [SecurityPermissionAttribute(SecurityAction.Demand, SerializationFormatter = true)]
            public virtual void GetObjectData(SerializationInfo info, StreamingContext context)
            {
                info.AddValue("Date", m_date);

                //获取类和基类的可序列化成员
                Type baseType = this.GetType().BaseType;
                var mi = FormatterServices.GetSerializableMembers(baseType, context);
                for (int i = 0; i < mi.Length; i++)
                {
                    info.AddValue(baseType.FullName + "+" + mi[i].Name, ((FieldInfo)mi[i]).GetValue(this));
                }
            }

            public override string ToString()
            {
                return string.Format("Name={0}, Date={1}", m_name, m_date);
            }
        }


        //序列化代理
        internal sealed class UniversalToLocalTimeSerializationSurrogate : ISerializationSurrogate
        {
            public void GetObjectData(object obj, SerializationInfo info, StreamingContext context)
            {
                info.AddValue("Date", ((DateTime)obj).ToUniversalTime().ToString("u"));
            }

            public object SetObjectData(object obj, SerializationInfo info, StreamingContext context, ISurrogateSelector selector)
            {
                return DateTime.ParseExact(info.GetString("Date"), "u", null).ToLocalTime();
            }
        }

        //使用SerializationBinder类来将对象反序列化成不同的类型
        internal sealed class Ver1ToVer2SerialisationBinder : SerializationBinder
        {
            public override Type BindToType(string assemblyName, string typeName)
            {
                AssemblyName assemVer1 = Assembly.GetExecutingAssembly().GetName();
                assemVer1.Version = new Version(1, 0, 0, 0);

                //如果从v1.0.0.0反序列化ver1对象，就把他转换为ver2对象
                if (assemblyName == assemVer1.ToString() && typeName == "Ver1")
                {
                    //return typeof(Ver2);
                }


                return Type.GetType(string.Format("{0}, {1}", typeName, assemblyName));
            }
        }

        static void Main(string[] args)
        {
            var objectGraph = new List<string> { "Jeff", "Kristin", "Aidan", "Grant" };
            Stream stream = SerialiseToMemory(objectGraph);
            stream.Position = 0; //为了演示，将其重置
            objectGraph = null;

            //反序列化
            objectGraph = (List<string>)DeserialiseFromMemory(stream);
            foreach (var s in objectGraph)
            {
                Console.WriteLine(s);
            }

            var derived = new Derived();
            stream = SerialiseToMemory(derived);
            stream.Position = 0;
            derived = (Derived)DeserialiseFromMemory(stream);
            Console.WriteLine(derived);

            //使用序列化代理
            using (var s = new MemoryStream())
            {
                IFormatter formatter = new BinaryFormatter();
                //构造代理对象
                SurrogateSelector ss = new SurrogateSelector();
                //告诉代理为DateTime使用代理序列化
                ss.AddSurrogate(typeof(DateTime), formatter.Context, new UniversalToLocalTimeSerializationSurrogate());
                //告诉formatter使用代理选择器
                formatter.SurrogateSelector = ss;
                DateTime localTimeBeforeSerialise = DateTime.Now;
                formatter.Serialize(s, localTimeBeforeSerialise);
                s.Position = 0;
                Console.WriteLine(new StreamReader(stream).ReadToEnd());
                //反序列化时间字符串将其转换成本地DateTime
                s.Position = 0;
                DateTime localTimeAfterDesrialise = (DateTime)formatter.Deserialize(s);
                Console.WriteLine("localTimeBeforeSerialise: {0}", localTimeBeforeSerialise);
                Console.WriteLine("localTimeAfterDesrialise:{0}", localTimeAfterDesrialise);
            }
        }

        private static object DeserialiseFromMemory(Stream stream)
        {
            //构造序列会格式化器
            BinaryFormatter formatter = new BinaryFormatter();
            return formatter.Deserialize(stream);
        }

        private static Stream SerialiseToMemory(object objectGraph)
        {
            //构造流来容纳序列化对象
            MemoryStream stream = new MemoryStream();

            //构造序列化格式化器来执行所有真正的工作
            BinaryFormatter formmater = new BinaryFormatter();

            //告诉格式化器将对象序列化到流中
            formmater.Serialize(stream, objectGraph);

            return stream;
        }
    }
}

using System;
using System.Text;
using System.Threading;

namespace Chapter14
{
    class Program
    {
        internal sealed class BoldInt32s : IFormatProvider, ICustomFormatter
        {
            //使用定制格式化器来实现将int32值标记<B></B>
            public Object GetFormat(Type formartType)
            {
                if (formartType == typeof(ICustomFormatter))
                    return this;
                return Thread.CurrentThread.CurrentCulture.GetFormat(formartType);
            }

            public string Format(string format, object arg,IFormatProvider formatProvider)
            {
                string s;
                IFormattable formattable = arg as IFormattable;
                if (formattable == null)
                {
                    s = arg.ToString();
                }
                else
                {
                    s = formattable.ToString(format, formatProvider);
                }
                if(arg.GetType()==typeof(Int32))
                {
                    return "<B>" + s + "</B>";
                }
                return s;
            }
        }
        static void Main(string[] args)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat(new BoldInt32s(), "{0} {1} {2:M}", "Kai", 123, DateTime.Now);
            Console.WriteLine(sb.ToString());

            //使用UTF8进行编码
            string s = "hi there";
            Encoding encodingUTF8 = Encoding.UTF8;
            byte[] encodedBytes = encodingUTF8.GetBytes(s);
            Console.WriteLine("Encoded bytes: " + BitConverter.ToString(encodedBytes));
            string decodedString = encodingUTF8.GetString(encodedBytes);
            Console.WriteLine("Decoded sting: " + decodedString);
        }
    }
}

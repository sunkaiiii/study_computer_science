using System;
using System.IO;

namespace CP10
{
    public static class StreamUtil
    {
        const int BufferSize = 8192;
        public static void Copy(Stream input,Stream output)
        {
            var buffer = new byte[BufferSize];
            int read;
            while((read=input.Read(buffer,0,buffer.Length))>0)
            {
                output.Write(buffer, 0, read);
            }
        }

        public static byte[] ReadFully(Stream input)
        {
            using (MemoryStream tempSream = new MemoryStream())
            {
                Copy(input, tempSream);
                return tempSream.ToArray();
            }
        }

        //包含扩展方法的StreamUtil类
        public static void TryCopyTo(this Stream input,Stream output)
        {
            var buffer = new byte[BufferSize];
            int read;
            while((read=input.Read(buffer,0,buffer.Length))>0)
            {
                output.Write(buffer, 0, read);
            }
        }

        public static byte[] TryReadFully(this Stream input)
        {
            using (MemoryStream tempStream = new MemoryStream())
            {
                input.TryCopyTo(tempStream);
                return tempStream.ToArray();
            }
        }
    }
}

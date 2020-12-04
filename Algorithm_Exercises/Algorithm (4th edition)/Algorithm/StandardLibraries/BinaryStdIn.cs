using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace StandardLibraries
{
    public sealed class BinaryStdIn
    {
        private static int buffer;
        private static int n;
        private static bool isInitialised;

        private BinaryStdIn() {  }

        private static void Initialise() 
        {
            buffer = 0;
            n = 0;
            fillBuffer();
            isInitialised = true;
        }

        private static void fillBuffer()
        {
            try
            {
                buffer = Console.In.Read();
                n = 8;
            }catch(Exception e)
            {
                buffer = -1;
                n = -1;
            }
        }

        public static bool IsEmpty()
        {
            if (!isInitialised)
            {
                Initialise();
            }
            return buffer == -1;
        }

        public static bool ReadBoolean()
        {
            if (IsEmpty())
                throw new Exception("The stream is closed");
            n--;
            bool bit = ((buffer >> n) & 1) == 1;
            if (n == 0)
                fillBuffer();
            return bit;
        }

        public static char ReadChar()
        {
            if (IsEmpty())
                throw new Exception("The stream is closed");
            int x;
            if (n==8)
            {
                x = buffer;
                fillBuffer();
                return (char)(x & 0xff);
            }

            x = buffer;
            x <<= (8 - n);
            int oldN = n;
            fillBuffer();
            if (IsEmpty())
                throw new Exception("The stream is closed");
            n = oldN;
            x |= (buffer >> n);
            return (char)(x & 0xff);
        }

        public static char ReadChar(int r)
        {
            if (r < 1 || r > 16) 
                throw new Exception("Illegal value of r = " + r);

            if (r == 8) 
                return ReadChar();
            int x = 0;
            for (int i = 0; i < r; i++)
            {
                x <<= 1;
                bool bit = ReadBoolean();
                if (bit) 
                    x |= 1;
            }
            return (char)x;
        }

        public static string ReadString()
        {
            if (IsEmpty())
                throw new Exception("The stream is closed");

            StringBuilder sb = new StringBuilder();
            while (!IsEmpty())
            {
                char c = ReadChar();
                sb.Append(c);
            }
            return sb.ToString();
        }

        public static short ReadShort()
        {
            short x = 0;
            for (int i = 0; i < 2; i++)
            {
                short c = (short)ReadChar();
                x <<= 8;
                x |= c;
            }
            return x;
        }

        public static int ReadInt()
        {
            int x = 0;
            for (int i = 0; i < 4; i++)
            {
                char c = ReadChar();
                x <<= 8;
                x |= c;
            }
            return x;
        }

        public static int ReadInt(int r)
        {
            if (r < 1 || r > 32) 
                throw new Exception("Illegal value of r = " + r);

            // optimize r = 32 case
            if (r == 32) return ReadInt();

            int x = 0;
            for (int i = 0; i < r; i++)
            {
                x <<= 1;
                bool bit = ReadBoolean();
                if (bit) x |= 1;
            }
            return x;
        }

        public static long ReadLong()
        {
            long x = 0;
            for (int i = 0; i < 8; i++)
            {
                char c = ReadChar();
                x <<= 8;
                x |= c;
            }
            return x;
        }

        public static double ReadDouble()
        {
            return BitConverter.Int64BitsToDouble(ReadLong());
        }

        public static float ReadFloat()
        {
            return (float)BitConverter.Int64BitsToDouble(ReadInt());
        }

        public static byte ReadByte()
        {
            char c = ReadChar();
            return (byte)(c & 0xff);
        }
    }
}

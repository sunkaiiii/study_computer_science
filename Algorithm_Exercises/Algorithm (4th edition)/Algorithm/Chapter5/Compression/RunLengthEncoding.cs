using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.Compression
{
    class RunLengthEncoding : ICompressMethod
    {
        public void Compress()
        {
            char cnt = (char)0;
            bool b, old = false;
            while(!BinaryStdIn.IsEmpty())
            {
                b = BinaryStdIn.ReadBoolean();
                if (b!=old)
                {
                    BinaryStdOut.Write(cnt);
                    cnt = (char)0;
                    old = !old;
                }
                else
                {
                    if (cnt == 255)
                    {
                        BinaryStdOut.Write(cnt);
                        cnt = (char)0;
                        BinaryStdOut.Write(cnt);
                    }
                }
                cnt++;
            }
            BinaryStdOut.Write(cnt);
        }

        public void Expand()
        {
            bool b = false;
            while(!BinaryStdIn.IsEmpty())
            {
                char cnt = BinaryStdIn.ReadChar();
                for (int i = 0; i < cnt; i++)
                {
                    BinaryStdOut.Write(b);
                }
                b = !b;
            }
        }
    }
}

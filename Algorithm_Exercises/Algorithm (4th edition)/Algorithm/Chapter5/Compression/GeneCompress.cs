using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.Compression
{
    class GeneCompress:ICompressMethod
    {
        public void Compress()
        {
            Alphabet DNA = new Alphabet("ACTG");
            string s = BinaryStdIn.ReadString();
            int n = s.Length;
            BinaryStdOut.Write(n);
            for(int i = 0; i<n;i++)
            {
                //将字符用双位编码代码来表示
                int d = DNA.ToIndex(s[i]);
                BinaryStdOut.Write(d, DNA.LgR());
            }
        }

        public void Expand()
        {
            Alphabet DNA = new Alphabet("ACTG");
            int w = DNA.LgR();
            int n = BinaryStdIn.ReadInt();
            for(int i = 0;i<n;i++)
            {
                var c = BinaryStdIn.ReadChar(w);
                BinaryStdOut.Write(DNA.ToChar(c));
            }
        }
    }
}

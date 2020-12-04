using Chapter5.StringST;
using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.Compression
{
    public class LZW : ICompressMethod
    {
        private readonly int R = 256;
        private readonly int L = 4096;
        private readonly int W = 12;
        public void Compress()
        {
            string input = BinaryStdIn.ReadString();
            TST<int> st = new TST<int>();
            for (int i = 0; i < R; i++)
            {
                st.Put("" + i, i);
            }
            int code = R + 1; //标记结束
            while (input.Length > 0)
            {
                string s = st.LongestPrefixOf(input); //匹配最长前缀
                BinaryStdOut.Write(st.Get(s), W);
                int t = s.Length;
                if (t < input.Length && code < L) //将s加入符号表
                {
                    st.Put(input.Substring(0, t + 1), code++);
                }
                input = input.Substring(t);
            }
            BinaryStdOut.Write(R, W);
        }

        public void Expand()
        {
            string[] st = new string[L];
            int i; // 下一个待补全的编码值
            for ( i = 0; i < R; i++)
            {
                st[i] = "" + i;
            }
            st[i++] = " ";//EOF
            int codeword = BinaryStdIn.ReadInt(W);
            string val = st[codeword];
            while(true)
            {
                BinaryStdOut.Write(val); //输出当前字符串
                codeword = BinaryStdIn.ReadInt(W);
                if (codeword == R)
                    break;
                string s = st[codeword]; //获取下一个编码
                if (i == codeword)
                    s = val + val[0]; //根据上一个字符串首字母得到编码的字符串
                if (i < L)
                    st[i++] = val + s[0]; //为编译表添加新的条目
                val = s;
            }
        }
    }
}

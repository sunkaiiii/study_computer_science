using StandardLibraries;
using System;
using System.Collections.Generic;
using System.Numerics;
using System.Security.Cryptography;
using System.Text;

namespace Chapter5.StringSearch
{
    public class RabinKarp:IStringSearch
    {
        private string Pat { get; }
        private long PatHash { get; set; }
        private int M { get => Pat.Length; }
        private long Q { get; } //一个很大的素数
        private readonly int R = 256;
        private long RM { get; set; }
        public RabinKarp(string pat)
        {
            this.Pat = pat;
            Q = LongRandomPrime();
            RM = 1;
            for (int i = 0; i < M-1; i++)
            {
                RM = (R * RM) % Q;
            }
            PatHash = Hash(pat, M);
        }

        private long LongRandomPrime()
        {
            return Numerics.GetPrime();
        }

        private long Hash(string key, int m)
        {
            long h = 0;
            for (int i = 0; i < M; i++)
            {
                h = (R * h + key[i]) % Q;
            }
            return h;
        }

        public int Search(string txt)
        {
            //在文本中查找相等的散列值
            int N = txt.Length;
            long txtHash = Hash(txt, M);
            if (PatHash == txtHash && Check(0))
                return 0; //一开始就匹配成功
            for (int i = M; i < N; i++)
            {
                //减去第一个数字，加上最后一个数字，再次检查匹配
                txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;
                txtHash = (txtHash * R + txt[i]) % Q;
                if (PatHash == txtHash)
                {
                    if (Check(i - M + 1))
                        return i - M + 1; //找到匹配
                }
            }
            return N;
        }

        private bool Check(int v)
        {
            return true;
        }
    }
}

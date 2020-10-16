using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringSearch
{
    public class BoyerMoore:IStringSearch
    {
        private int[] Right { get; set; }
        private string Pat { get; }
        public BoyerMoore(string pat)
        {
            this.Pat = pat;
            int M = pat.Length;
            int R = 256;
            Right = new int[R];
            //构造跳跃表
            for (int c = 0; c < R; c++)
            {
                Right[c] = -1; //不包含在模式字符串中的字符的值为-1
            }
            for (int j = 0; j < M; j++)
            {
                Right[pat[j]] = j; //包含在模式字符串中的字符值为它在其中出现的最右位置
            }
        }

        public int Search(string txt)
        {
            int N = txt.Length;
            int M = Pat.Length;
            int skip;
            for (int i = 0; i < N-M; i++)
            {
                //从右边检测是否匹配
                skip = 0;
                for (int j = M-1; j >=0; j--)
                {
                    if(Pat[j]!=txt[i+j]) //不匹配
                    {
                        skip = j - Right[txt[i + j]];
                        if (skip < 1)
                            skip = 1;
                        break;
                    }
                }
                if (skip == 0)
                    return i;
            }
            return N;
        }
    }
}

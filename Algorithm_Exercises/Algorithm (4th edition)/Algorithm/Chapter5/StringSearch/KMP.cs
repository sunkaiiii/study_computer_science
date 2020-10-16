using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.StringSearch
{
    public class KMP:IStringSearch
    {
        private string Pat { get; set; }
        private int[,] Dfa { get;  }
        public KMP(string pat)
        {
            //由模式构造DFA
            this.Pat = pat;
            int M = pat.Length;
            int R = 256;
            Dfa = new int[R,M];
            Dfa[pat[0], 0] = 1;
            for (int X = 0,j=1;j<M;j ++)
            {
                //计算dfa[][j]
                for(int c = 0; c < R; c++)
                {
                    Dfa[c, j] = Dfa[c, X]; //匹配失败情况下的值
                }
                Dfa[Pat[j], j] = j + 1; //匹配成功情况下的值
                X = Dfa[Pat[j], X]; //更新重启状态
            }
        }

        public int Search(string txt)
        {
            int i, j, N = txt.Length, M = Pat.Length;
            for (i = 0,j=0; i < N&&j<M; i++)
            {
                j = Dfa[txt[i], j];
            }
            if (j == M)
                return i - M; //找到匹配，到达模式字符串的结尾
            else
                return N; //未找到匹配，到达文本字符串的结尾
        }
    }
}

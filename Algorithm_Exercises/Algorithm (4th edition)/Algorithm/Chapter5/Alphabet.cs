using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace Chapter5
{
    public class Alphabet
    {
        /**
     *  The binary alphabet { 0, 1 }.
     */
        public static readonly Alphabet BINARY = new Alphabet("01");

        /**
         *  The octal alphabet { 0, 1, 2, 3, 4, 5, 6, 7 }.
         */
        public static readonly Alphabet OCTAL = new Alphabet("01234567");

        /**
         *  The decimal alphabet { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
         */
        public static readonly Alphabet DECIMAL = new Alphabet("0123456789");

        /**
         *  The hexadecimal alphabet { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F }.
         */
        public static readonly Alphabet HEXADECIMAL = new Alphabet("0123456789ABCDEF");

        /**
         *  The DNA alphabet { A, C, T, G }.
         */
        public static readonly Alphabet DNA = new Alphabet("ACGT");

        /**
         *  The lowercase alphabet { a, b, c, ..., z }.
         */
        public static readonly Alphabet LOWERCASE = new Alphabet("abcdefghijklmnopqrstuvwxyz");

        /**
         *  The uppercase alphabet { A, B, C, ..., Z }.
         */

        public static readonly Alphabet UPPERCASE = new Alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        /**
         *  The protein alphabet { A, C, D, E, F, G, H, I, K, L, M, N, P, Q, R, S, T, V, W, Y }.
         */
        public static readonly Alphabet PROTEIN = new Alphabet("ACDEFGHIKLMNPQRSTVWY");

        /**
         *  The base-64 alphabet (64 characters).
         */
        public static readonly Alphabet BASE64 = new Alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

        /**
         *  The ASCII alphabet (0-127).
         */
        public static readonly Alphabet ASCII = new Alphabet(128);

        /**
         *  The extended ASCII alphabet (0-255).
         */
        public static readonly Alphabet EXTENDED_ASCII = new Alphabet(256);

        /**
         *  The Unicode 16 alphabet (0-65,535).
         */
        public static readonly Alphabet UNICODE16      = new Alphabet(65536);

        private char[] alphabet;
        private int[] inverse;

        //字符的数量
        public int R { get; }

        //从给定的字符集初始化一个新字母表
        public Alphabet(string alpha)
        {
            bool[] unicode = new bool[char.MaxValue];
            for (int i = 0; i < alpha.Length; i++)
            {
                char c = alpha[i];
                if (unicode[c])
                    throw new Exception("Illegal alphabet: repeated character = '" + c + "'");
                unicode[c] = true;
            }
            alphabet = alpha.ToCharArray();
            R = alpha.Length;
            inverse = new int[char.MaxValue];
            for (int i = 0; i < inverse.Length; i++)
            {
                inverse[i] = -1;
            }
            for (int c = 0; c < R; c++)
            {
                inverse[alphabet[c]] = c;
            }
        }

        private Alphabet(int radix)
        {
            this.R = radix;
            alphabet = new char[R];
            inverse = new int[R];

            for (int i = 0; i < R; i++)
                alphabet[i] = (char)i;
            for (int i = 0; i < R; i++)
                inverse[i] = i;
        }

        public Alphabet() : this(256) { }

        public bool Contains(char c)
        {
            return inverse[c] != -1;
        }

        public int LgR()
        {
            int lgR = 0;
            for(int t = R - 1; t >= 1; t /= 2)
            {
                lgR++;
            }
            return lgR;
        }

        public int ToIndex(char c)
        {
            if(c>=inverse.Length||inverse[c]==-1)
            {
                throw new Exception("Character " + c + " not in alphabet");
            }
            return inverse[c];
        }

        public int[] ToIndices(string s)
        {
            char[] source = s.ToCharArray();
            int[] target = new int[s.Length];
            for (int i = 0; i < source.Length; i++)
            {
                target[i] = ToIndex(source[i]);
            }

            return target;
        }

        public char ToChar(int index)
        {
            return alphabet[index];
        }

        public string ToChars(int[] indices)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < indices.Length; i++)
            {
                sb.Append(ToChar(indices[i]));
            }
            return sb.ToString();
        }
    }
}

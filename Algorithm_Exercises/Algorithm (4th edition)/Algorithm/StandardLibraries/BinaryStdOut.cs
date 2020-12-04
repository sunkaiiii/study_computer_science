using System;
using System.Collections.Generic;
using System.Text;

namespace StandardLibraries
{
    public sealed class BinaryStdOut
    {
        private static int buffer;
        private static int n;
        private static bool isInitialised;

        private BinaryStdOut() { }

        private static void Initialise()
        {
            buffer = 0;
            n = 0;
            isInitialised = true;
        }

        private static void WriteBit(bool bit)
        {
            if (!isInitialised)
                Initialise();

            // add bit to buffer
            buffer <<= 1;
            if (bit) buffer |= 1;

            // if buffer is full (8 bits), write out as a single byte
            n++;
            if (n == 8)
                ClearBuffer();
        }


        /**
          * Writes the 8-bit byte to standard output.
          */
        private static void WriteByte(int x)
        {
            if (!isInitialised)
                Initialise();

            // optimized if byte-aligned
            if (n == 0)
            {
                try
                {
                    Console.Write(x);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.StackTrace);
                }
                return;
            }

            // otherwise write one bit at a time
            for (int i = 0; i < 8; i++)
            {
                bool bit = ((x >> (8 - i - 1)) & 1) == 1;
                WriteBit(bit);
            }
        }

        // write out any remaining bits in buffer to standard output, padding with 0s
        private static void ClearBuffer()
        {
            if (!isInitialised)
                Initialise();

            if (n == 0) return;
            if (n > 0) buffer <<= (8 - n);
            try
            {
                Console.Write(buffer);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            n = 0;
        }

        /**
  * Flushes standard output, padding 0s if number of bits written so far
  * is not a multiple of 8.
  */
        public static void Flush()
        {
            ClearBuffer();
            try
            {
                Console.Out.Flush();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        /**
  * Writes the specified bit to standard output.
  * @param x the {@code boolean} to write.
  */
        public static void Write(bool x)
        {
            WriteBit(x);
        }


        /**
          * Writes the 8-bit byte to standard output.
          * @param x the {@code byte} to write.
          */
        public static void Write(byte x)
        {
            WriteByte(x & 0xff);
        }

        /**
  * Writes the 32-bit int to standard output.
  * @param x the {@code int} to write.
  */
        public static void Write(int x)
        {
            WriteByte((x >> 24) & 0xff);
            WriteByte((x >> 16) & 0xff);
            WriteByte((x >> 8) & 0xff);
            WriteByte((x >> 0) & 0xff);
        }

        /**
  * Writes the <em>r</em>-bit int to standard output.
  * @param x the {@code int} to write.
  * @param r the number of relevant bits in the char.
  * @throws IllegalArgumentException if {@code r} is not between 1 and 32.
  * @throws IllegalArgumentException if {@code x} is not between 0 and 2<sup>r</sup> - 1.
  */
        public static void Write(int x, int r)
        {
            if (r == 32)
            {
                Write(x);
                return;
            }
            if (r < 1 || r > 32) throw new Exception("Illegal value for r = " + r);
            if (x < 0 || x >= (1 << r)) throw new Exception("Illegal " + r + "-bit char = " + x);
            for (int i = 0; i < r; i++)
            {
                bool bit = ((x >> (r - i - 1)) & 1) == 1;
                WriteBit(bit);
            }
        }

        /**
  * Writes the 64-bit double to standard output.
  * @param x the {@code double} to write.
  */
        public static void Write(double x)
        {
            Write(BitConverter.DoubleToInt64Bits(x));
        }

        /**
  * Writes the 64-bit long to standard output.
  * @param x the {@code long} to write.
  */
        public static void Write(long x)
        {
            WriteByte((int)((x >> 56) & 0xff));
            WriteByte((int)((x >> 48) & 0xff));
            WriteByte((int)((x >> 40) & 0xff));
            WriteByte((int)((x >> 32) & 0xff));
            WriteByte((int)((x >> 24) & 0xff));
            WriteByte((int)((x >> 16) & 0xff));
            WriteByte((int)((x >> 8) & 0xff));
            WriteByte((int)((x >> 0) & 0xff));
        }

        /**
  * Writes the 32-bit float to standard output.
  * @param x the {@code float} to write.
  */
        public static void Write(float x)
        {
            Write(BitConverter.DoubleToInt64Bits(x));
        }
        /**
  * Writes the 16-bit int to standard output.
  * @param x the {@code short} to write.
  */
        public static void Write(short x)
        {
            WriteByte((x >> 8) & 0xff);
            WriteByte((x >> 0) & 0xff);
        }


        /**
          * Writes the 8-bit char to standard output.
          * @param x the {@code char} to write.
          * @throws IllegalArgumentException if {@code x} is not betwen 0 and 255.
          */
        public static void Write(char x)
        {
            if (x < 0 || x >= 256) throw new Exception("Illegal 8-bit char = " + x);
            WriteByte(x);
        }

        /**
  * Writes the <em>r</em>-bit char to standard output.
  * @param x the {@code char} to write.
  * @param r the number of relevant bits in the char.
  * @throws IllegalArgumentException if {@code r} is not between 1 and 16.
  * @throws IllegalArgumentException if {@code x} is not between 0 and 2<sup>r</sup> - 1.
  */
        public static void Write(char x, int r)
        {
            if (r == 8)
            {
                Write(x);
                return;
            }
            if (r < 1 || r > 16) throw new Exception("Illegal value for r = " + r);
            if (x >= (1 << r)) throw new Exception("Illegal " + r + "-bit char = " + x);
            for (int i = 0; i < r; i++)
            {
                bool bit = ((x >> (r - i - 1)) & 1) == 1;
                WriteBit(bit);
            }
        }


        /**
          * Writes the string of 8-bit characters to standard output.
          * @param s the {@code String} to write.
          * @throws IllegalArgumentException if any character in the string is not
          * between 0 and 255.
          */
        public static void Write(string s)
        {
            for (int i = 0; i < s.Length; i++)
                Write(s[i]);
        }

        /**
  * Writes the string of <em>r</em>-bit characters to standard output.
  * @param s the {@code String} to write.
  * @param r the number of relevants bits in each character.
  * @throws IllegalArgumentException if r is not between 1 and 16.
  * @throws IllegalArgumentException if any character in the string is not
  * between 0 and 2<sup>r</sup> - 1.
  */
        public static void Write(string s, int r)
        {
            for (int i = 0; i < s.Length; i++)
                Write(s[i], r);
        }
    }
}

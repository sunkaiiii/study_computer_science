using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace StandardLibraries
{
    public class Scanner
    {
        string currentWord;
        string currentLine;
        System.IO.TextReader reader;
        public Scanner(System.IO.TextReader reader)
        {
            this.reader = reader;
        }

        private void ReadNextLine()
        {
            if(currentLine!=null)
            {
                return;
            }
            currentLine = reader.ReadLine();
        }

        private void ReadNextWord()
        {
            if(currentWord!=null)
            {
                return;
            }
            System.Text.StringBuilder sb = new StringBuilder();
            char nextChar;
            int next;
            do
            {
                next = reader.Read();
                if (next < 0)
                    break;
                nextChar = (char)next;
                if (char.IsWhiteSpace(nextChar))
                    break;
                sb.Append(nextChar);
            } while (true);
            while ((reader.Peek() >= 0) && (char.IsWhiteSpace((char)reader.Peek())))
                reader.Read();
            if (sb.Length > 0)
                currentWord = sb.ToString();
            else
                currentWord = null;
        }


        public bool HasNextChar()
        {
            ReadNextWord();
            return currentWord != null && currentWord.Length > 0 && !char.IsWhiteSpace(currentWord[0]);
        }

        public bool HasNextLine()
        {
            ReadNextLine();
            return currentLine != null;
        }

        private void ClearCache()
        {
            currentWord = null;
            currentLine = null;
        }

        public string ReadLine()
        {
            try
            {
                ReadNextLine();
                return currentLine;
            }
            finally
            {
                ClearCache();
            }
        }

        public bool IsEmpty()
        {
            return reader.Peek() >= 0;
        }

        public string ReadAll()
        {
            ClearCache();
            return reader.ReadToEnd();
        }

        public bool HasNextInt()
        {
            ReadNextWord();
            if (currentWord == null)
                return false;
            int dummy;
            return int.TryParse(currentWord, out dummy);
        }

        public int ReadInt()
        {
            try
            {
                ReadNextWord();
                return int.Parse(currentWord);
            }
            finally
            {
                ClearCache();
            }

        }

        public bool HasNextDouble()
        {
            ReadNextWord();
            if (currentWord == null)
                return false;
            double dummy;
            return double.TryParse(currentWord, out dummy);
        }

        public bool HasNextLong()
        {
            ReadNextWord();
            if(currentWord==null)
            {
                return false;
            }
            long dummy;
            return long.TryParse(currentWord, out dummy);
        }

        public double ReadDouble()
        {
            try
            {
                ReadNextWord();
                return double.Parse(currentWord);
            }finally
            {
                ClearCache();
            }

        }

        public short ReadShort()
        {
            try
            {
                ReadNextWord();
                return short.Parse(currentWord);
            }finally
            {
                ClearCache();
            }

        }

        public long ReadLong()
        {
            try
            {
                ReadNextWord();
                return long.Parse(currentWord);
            }finally
            {
                ClearCache();
            }

        }

        public float ReadFloat()
        {
            try
            {
                ReadNextWord();
                return float.Parse(currentWord);
            }finally
            {
                ClearCache();
            }
 
        }

        public bool? ReadBool()
        {
            ReadNextWord();
            try
            {
                string value = currentWord;
                if ("true".Equals(value.ToLower())) return true;
                if ("false".Equals(value.ToLower())) return false;
                if ("1".Equals(value)) return true;
                if ("0".Equals(value)) return false;
                return null;
            }finally
            {
                ClearCache();
            }

        }

        public char ReadChar()
        {
            ReadNextWord();
            char returnValue = currentWord[0];
            currentWord = new string(currentWord.ToCharArray(), 1, currentWord.ToCharArray().Length - 1);
            return returnValue;
        }

        public string[] ReadAllLines()
        {
            ClearCache();
            List<string> result = new List<string>();
            string line;
            while ((line=ReadLine())!=null)
            {
                result.Add(line);
            }
            return result.ToArray() ;
        }

        public int[] ReadInts()
        {
            List<int> result = new List<int>();
            while(HasNextInt())
            {
                result.Add(ReadInt());
            }
            return result.ToArray();
        }

        public double[] ReadDoubles()
        {
            List<double> result = new List<double>();
            while(HasNextDouble())
            {
                result.Add(ReadDouble());
            }
            return result.ToArray();
        }

        public long[] ReadLongs()
        {
            List<long> result = new List<long>();
            while(HasNextLong())
            {
                result.Add(ReadLong());
            }
            return result.ToArray();
        }

        public string[] ReadStrings()
        {
            List<string> result = new List<string>();
            while(HasNext())
            {
                result.Add(Read());
            }
            return result.ToArray();
        }

        public string Read()
        {
            try
            {
                ReadNextWord();
                return currentWord;
            }
            finally
            {
                ClearCache();
            }
        }
        public bool HasNext()
        {
            ReadNextWord();
            return currentWord != null;
        }
    }
}

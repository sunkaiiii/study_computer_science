using System;
using System.Collections.Generic;
using System.Text;

namespace StandardLibraries
{
    public class Scanner
    {
        string currentWord;
        System.IO.TextReader reader;
        public Scanner(System.IO.TextReader reader)
        {
            this.reader = reader;
            ReadNextWord();
        }

        private void ReadNextWord()
        {
            System.Text.StringBuilder sb = new StringBuilder();
            char nextChar;
            int next;
            do
            {
                char peek = (char)reader.Peek();
                while (sb.Length == 0 && (char.IsWhiteSpace(peek) || peek =='\r'||peek=='\n'||char.IsSeparator(peek)))
                {
                    reader.Read();
                    peek = (char)reader.Peek();
                }
                    
                next = reader.Read();
                if (next < 0)
                    break;
                nextChar = (char)next;
                if (char.IsWhiteSpace(nextChar)||nextChar.ToString().Equals(Environment.NewLine))
                    break;
                sb.Append(nextChar);
            } while (true);
            if (sb.Length > 0)
                currentWord = sb.ToString();
            else
                currentWord = null;
        }

        public string ReadALine()
        {
            string currentLine;
            try
            {
                currentLine = reader.ReadLine();
            }catch(Exception e)
            {
                Console.WriteLine(e.Message);
                currentLine = null;
            }
            ReadNextWord();
            return currentLine;
        }

        public bool IsEmpty()
        {
            return reader.Peek() >= 0;
        }

        public string ReadAll()
        {
            return reader.ReadToEnd();
            
        }

        public bool HasNextInt()
        {
            if (currentWord == null)
                return false;
            int dummy;
            return int.TryParse(currentWord, out dummy);
        }

        public int NextInt()
        {
            ReadNextWord();
            return int.Parse(currentWord);
        }

        public bool HasNextDouble()
        {
            if (currentWord == null)
                return false;
            double dummy;
            return double.TryParse(currentWord, out dummy);
        }

        public double NextDouble()
        {
            ReadNextWord();
            return double.Parse(currentWord);
        }

        public short ReadShort()
        {
            ReadNextWord();
            return short.Parse(currentWord);
        }

        public long ReadLong()
        {
            try
            {
                return long.Parse(currentWord);
            }
            finally
            {
                ReadNextWord();
            }
        }

        public float ReadFloat()
        {
            ReadNextWord();
            return float.Parse(currentWord);  
        }

        public bool? ReadBool()
        {
            ReadNextWord();
            string value = currentWord;
            if ("true".Equals(value.ToLower())) return true;
            if ("false".Equals(value.ToLower())) return false;
            if ("1".Equals(value)) return true;
            if ("0".Equals(value)) return false;
            return null;
        }

        public bool HasNext()
        {
            return currentWord != null;
        }
    }
}

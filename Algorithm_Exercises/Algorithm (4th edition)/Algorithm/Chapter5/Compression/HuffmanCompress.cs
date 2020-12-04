using Chapter1;
using Chapter2;
using StandardLibraries;

namespace Chapter5.Compression
{
    class HuffmanCompress : ICompressMethod
    {
        private readonly int R = 256;
        public void Compress()
        {
            //读取输入
            string s = BinaryStdIn.ReadString();
            char[] input = s.ToCharArray();
            //统计频率
            int[] freq = new int[R];
            for (int i = 0; i < input.Length; i++)
                freq[input[i]]++;
            Node root = BuildTrie(freq);
            //构造编译表
            string[] st = BuildCode(root);
            Writetrie(root);
            //打印总字符数
            BinaryStdOut.Write(input.Length);

            for(int i=0;i<input.Length;i++)
            {
                string code = st[input[i]];
                for(int j=0;j<code.Length;j++)
                {
                    if (code[j] == '1')
                        BinaryStdOut.Write(true);
                    else
                        BinaryStdOut.Write(false);
                }
            }
        }

        public void Expand()
        {
            Node root = ReadTrie();
            int n = BinaryStdIn.ReadInt();
            for (int i = 0; i < n; i++)
            {
                var x = root;
                while (!x.isLeaf())
                {
                    if (BinaryStdIn.ReadBoolean())
                    {
                        x = x.Right;
                    }
                    else
                    {
                        x = x.Left;
                    }
                }
                BinaryStdOut.Write(x.Ch);
            }
        }

        private string[] BuildCode(Node root)
        {
            var st = new string[R];
            BuildCode(st, root, "");
            return st;
        }

        private void BuildCode(string[] st, Node x,string s)
        {
            if(x.isLeaf())
            {
                st[x.Ch] = s;
                return;
            }
            BuildCode(st, x.Left, s + '0');
            BuildCode(st, x.Right, s + '1');
        }

        private Node BuildTrie(int[] freq)
        {
            MinPQ<Node> pq = new MinPQ<Node>();
            for (char c = (char)0; c < (char)R; c++)
            {
                if(freq[c] > 0)
                {
                    pq.Insert(new Node(c, freq[c], null, null));
                }
            }
            while(pq.Size>1)
            {
                Node x = pq.Delete();
                Node y = pq.Delete();
                Node parent = new Node('\0', x.freq + y.freq, x, y);
                pq.Insert(parent);
            }
            return pq.Delete();
        }
        

        private static Node ReadTrie()
        {
            if (BinaryStdIn.ReadBoolean())
                return new Node(BinaryStdIn.ReadChar(), 0, null, null);
            return new Node('\0', 0, ReadTrie(), ReadTrie());
        }

        private static void Writetrie(Node x)
        {
            if(x.isLeaf())
            {
                BinaryStdOut.Write(true);
                BinaryStdOut.Write(x.Ch);
                return;
            }
            BinaryStdOut.Write(false);
            Writetrie(x.Left);
            Writetrie(x.Right);
        }
    }
}

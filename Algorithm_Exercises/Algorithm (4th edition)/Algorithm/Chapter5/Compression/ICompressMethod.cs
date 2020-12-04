using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter5.Compression
{
    interface ICompressMethod
    {
        void Compress();
        void Expand();
    }
}

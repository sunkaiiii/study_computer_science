using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class DataContext
    {
        static readonly Random _rand = new Random();
        public int RowCount { get; }
        public DataContext()
        {
            RowCount = _rand.Next(1, 1_000_000_000);
        }
    }
}

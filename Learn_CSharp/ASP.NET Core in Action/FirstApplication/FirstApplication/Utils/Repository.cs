using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class Repository
    {
        private readonly DataContext _dataContext;
        public Repository(DataContext d)
        {
            _dataContext = d;
        }
        public int RowCount => _dataContext.RowCount; //RowCount returns the same value as the current instance of DataContext

    }
}

using System;
using System.Collections.Generic;

namespace CP1
{
    public class ProductNameComparer : IComparer<Product>
    {
        public ProductNameComparer()
        {
        }

        //c#2 引入泛型接口
        public int Compare(Product x, Product y)
        {
            return string.Compare(x.Name, y.Name, StringComparison.Ordinal);
        }
    }
}

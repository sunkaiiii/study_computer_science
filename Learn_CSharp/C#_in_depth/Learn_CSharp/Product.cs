using System;
using System.Collections.Generic;

namespace CP1
{
    public class Product
    {
        //c# 3 自动属性
        public string Name { get; private set; } //
        public decimal Price { get; private set; }

        //C#4 命名实参抹除易变性
        readonly string code;
        public string Code { get { return code; } }

        //C# 2可空类型
        decimal? onsalePrice;
        public decimal? OnSalePrice
        {
            get { return onsalePrice; }
            private set { onsalePrice = value; }
        }

        public int SupplierID { get; set; }

        //C# 4可选参数和默认值
        public Product(string name, decimal price,string code, decimal? onsalePrice=null,int supplierID=100)
        {
            this.Name = name;
            this.Price = price;
            this.code = code;
            this.onsalePrice = onsalePrice;
            this.SupplierID = supplierID;
        }

        public Product() { }

        //C#2 引入泛型
        public static List<Product> GetSampleProducts()
        {
            //C#3引入简化初始化
            List<Product> list = new List<Product>
            {
                new Product("1", 1m,"2"),
                new Product("2", 2m,"2"),
                new Product(name:"2",price:2,code:"3") //C#4命名实参
            };
            return list;
        }

        public override string ToString()
        {
            return string.Format("{0}: {1}", Name, Price);
        }
    }
}

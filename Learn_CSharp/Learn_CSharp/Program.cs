using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using CP1;

namespace Learn_CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Product> products = Product.GetSampleProducts();
            products.Sort(new ProductNameComparer());
            foreach(Product product in products)
            {
                Console.WriteLine(product);
            }
            //C# 2引入委托
            products.Sort(delegate (Product x, Product y)
            {
                return String.Compare(x.Name, y.Name);
            });

            //C# 3中引入lambda表达式
            products.Sort((x, y) => String.Compare(x.Name, y.Name));

            
            products = Product.GetSampleProducts();
            //C# 3中使用扩展方法进行排序，这个操作不会修改源列表
            products.Reverse();
            foreach (Product product in products.OrderBy(p=>p.Name))
            {
                Console.WriteLine(product);
            }
            foreach (Product product in products)
            {
                Console.WriteLine(product);
            }

            //C# 2对查询进行的改进
            Predicate<Product> test = delegate (Product p) { return p.Price > 10m; };
            List<Product> matches = products.FindAll(test);
            Action<Product> print = Console.WriteLine;
            matches.ForEach(print);
            //也可以放在同一个句子里
            products.FindAll(delegate (Product p) { return p.Price > 10m; }).ForEach(Console.WriteLine);

            //使用C# 3 lambda表达式来进行查询
            foreach(Product product in products.Where(p=>p.Price>10m))
            {
                Console.WriteLine(product);
            }

            //使用可空类型，类显示促销价格未知的产品
            foreach(Product product in products.Where(p=>p.OnSalePrice==null))
            {
                Console.WriteLine(product);
            }

            //C# 3 LINQ
            //将实例产品和供货商连接起来
            //并对产品使用价格过滤器
            //先按供货商进行排序，再按产品名进行排序
            //最后打印每个匹配的供货商名称和产品名称
            products = Product.GetSampleProducts();
            List<Supplier> suppliers = Supplier.GetSampleSuppliers();
            var filtered = from p in products
                           join s in suppliers
                           on p.SupplierID equals s.SupplierID
                           where p.Price > 10
                           orderby s.Name, p.Name
                           select new { SupplierName = s.Name, ProductName = p.Name };
            foreach(var v in filtered)
            {
                Console.WriteLine("Supplier={0}; Product={1}", v.SupplierName, v.ProductName);
            }

            //使用LINQ对XML文件进行处理
            XDocument doc = XDocument.Load("data.xml");
            filtered = from p in doc.Descendants("Product")
                           join s in doc.Descendants("Supplier")
                            on (int)p.Attribute("SupplierID")
                            equals (int)s.Attribute("SupplierID")
                           where (decimal)p.Attribute("Price") > 10
                           orderby (string)s.Attribute("Name"),
                                    (string)s.Attribute("Name")
                           select new
                           {
                               SupplierName = (string)s.Attribute("Name"),
                               ProductName = (string)p.Attribute("Name")
                           };
            foreach (var v in filtered)
            {
                Console.WriteLine("Supplier={0}; Product={1}", v.SupplierName, v.ProductName);
            }

        }
    }
}

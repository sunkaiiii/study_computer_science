using System;
using System.IO;
using System.Linq;
using System.Net;

namespace CP10
{
    class Program
    {
        static void Main(string[] args)
        {
            //使用StreamUtil将Web响应复制到一个文件
            var request = WebRequest.Create("https://www.google.com");
            using (WebResponse response = request.GetResponse())
            using (Stream responseStream = response.GetResponseStream())
            using (FileStream output = File.Create("response.dat"))
            {
                StreamUtil.Copy(responseStream, output);
                //使用扩展方法
                responseStream.TryCopyTo(output);
            }

            //空引用的扩展方法
            object y = null;
            Console.WriteLine(y.IsNull());
            y = new object();
            Console.WriteLine(y.IsNull());

            var collection = Enumerable.Range(0, 10).Where(x=>x%2!=0).Reverse().Select(x=>new { Original = x, SquareRoot = Math.Sqrt(x) });
            foreach(var element in collection)
            {
                Console.WriteLine("sqrt({0})={1}",element.Original,element.SquareRoot);
            }

            //根据两个属性对序列进行排序
            var collection2 = Enumerable.Range(-5, 11)
                .Select(x => new { Orignal = x, Square = x * x })
                .OrderBy(x => x.Square)
                .ThenBy(x => x.Orignal);
            foreach (var element in collection2)
            {
                Console.WriteLine(element);

            }
            String a = "123";
            String b = "123";
            String c = new string("123");
            Console.WriteLine(a == c);
        }
    }
}

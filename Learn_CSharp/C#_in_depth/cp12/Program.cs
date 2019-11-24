using CP11;
using CP12;
using System;
using System.ComponentModel;
using System.Linq;
using System.Xml.Linq;

namespace CP12
{
    class Program
    {
        static void Main(string[] args)
        {
            //使用模拟查询类的简单查询表达式
            var query = from x in new FakeQuery<string>()
                        where x.StartsWith("abc")
                        select x.Length;
            double mean = query.Average();

            //LINQ to XML
            var element = new XElement("root", new XElement("child", new XElement("grandchild", "text")), new XElement("other-child"));
            Console.WriteLine(element);
            //从实例用户中创建元素
            var users = new XElement("users", SampleData.AllUsers.Select(user => new XElement("user", new XAttribute("name", user.Name), new XAttribute("type", user.UserType))));
            Console.WriteLine(users);
            //创建文本节点元素
            var developers = new XElement("developers", from user in SampleData.AllUsers
                                                        where user.UserType == UserType.Developer
                                                        select new XElement("developer", user.Name));
            Console.WriteLine(developers);

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //显示XML结构中的用户
            var root = XmlSampleData.GetElement();
            var query2 = root.Element("users").Elements().Select(user => new
            {
                Name = (string)user.Attribute("name"),
                UserType = (string)user.Attribute("type")
            });
            foreach(var user in query2)
            {
                Console.WriteLine("{0}: {1}", user.Name, user.UserType);
            }

            var q3 = Enumerable.Range(0, 100).RandomElement(new Random());
            Console.WriteLine(q3);
        }
    }
}

using System;
using System.Collections.Generic;

namespace CP8
{
    class Program
    {
         public struct Foo
        {
            public int Value { get; private set; }
            public Foo(int value):this() //使用结构时，显示的调用一个无参构造函数
            {
                this.Value = value;
            }
        }

        static void Main(string[] args)
        {
            //使用C# 3的简化初始化来创建Person
         
            Person tom3 = new Person() { Name = "Tom", Age = 9 };
            Person tom4 = new Person() { Name = "Tom", Age = 9 };
            Person tom5 = new Person() { Name = "Tom", Age = 9 };

            var family = new Person[]
            {
                new Person{Name="Hello",Age=33},
                new Person{Name="Hello",Age=33},
                new Person{Name="Hello",Age=33},
                new Person{Name="Hello",Age=33},
            };

            //为嵌入对象设置属性
            Person tom = new Person("Tom")
            {
                Age = 9,
                Home = { Country = "UK", Town = "Reading" }
            };

            //简化初始化集合
            var names = new List<string>
            {
                "Holly","Jon","Tom","Robin","William"
            };

            Dictionary<string, int> nameAgeMap = new Dictionary<string, int>
            {
                {"Holly",36 },
                {"Jon",36 },
                {"Tom",9 }
            };

            //创建具有Name和Age属性的匿名类型对象
            var tom2 = new { Name = "Tom", Age = 9 };
            var holly = new { Name = "Holly", Age = 36 };
            var jon = new { Name = "jon", Age = 36 };

            //匿名类型填充数组
            var families = new[]
            {
                new { Name = "Tom", Age = 9 },
                new { Name = "Holly", Age = 36 },
                new { Name = "jon", Age = 36 },
            };

            int totalAge = 0;
            foreach(var person in families)
            {
                totalAge += person.Age;
            }
            Console.WriteLine("Total age: {0}", totalAge);

            //投影初始化程序
            //这里obj第一个属性的名称就是Name，值就是tom.Name的值
            var obj=new { tom.Name, IsAdult = (tom.Age >= 18) };
            List<Person> familiesw2 = new List<Person>
            {
                new Person{Name="Holly",Age=16},
                new Person{Name="Jon",Age=36},
                new Person{Name="Tom",Age=9}
            };

            //从一个person对象转化成一个名字和一个成年的标志
            var conveted = familiesw2.ConvertAll(delegate (Person person)
              { return new { person.Name, IsAdult = (person.Age >= 18) }; });

            foreach(var person in conveted)
            {
                Console.WriteLine("{0} is an adult? {1}", person.Name, person.IsAdult);
            }
        }
    }
}

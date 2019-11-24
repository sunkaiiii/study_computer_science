using System;
using System.Collections.Generic;

namespace CP8
{
    public class Person
    {
        public string Name { get;  set; } //声明共有的取值方法
        public int Age { get;  set; }
        private static int InstanceCounter { get; set; } //声明私有的静态属性和锁
        private static readonly object counterLock = new object();

        List<Person> friends = new List<Person>();
        Location home = new Location();
        public Location Home { get { return home; } }

        public Person() { }
        public Person(string name)
        {
            Name = name;
        }

        public void InstanceCountingPerson(string name,int age)
        {
            Name = name;
            Age = age;
            lock(counterLock) //访问静态属性时使用锁
            {
                InstanceCounter++;
            }
        }

        public class Location
        {
            public string Country { get; set; }
            public string Town { get; set; }
        }
    }
}

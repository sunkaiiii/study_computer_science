using System;
using System.Collections.Generic;
using System.Text;

namespace CP2
{
    delegate void StringProcessor(string input); //声明委托类型
    class Person
    {
        string name;
        public Person(string name) { this.name = name; }
        public void Say(String message)
        {
            Console.WriteLine("{0} says: {1}", name, message);
        }
    }

    class Background
    {
        public static void Note(string note)
        {
            Console.WriteLine("({0})", note);
        }
    }

}

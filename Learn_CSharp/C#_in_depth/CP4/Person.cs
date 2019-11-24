using System;
namespace CP4
{
    public class Person
    {
        DateTime birth;
        DateTime? death;
        string name;
        
        public TimeSpan Age
        {
            get
            {
                if(death==null) //检查hasValue
                {
                    return DateTime.Now - birth;
                }
                else
                {
                    return death.Value - birth;
                }
            }
        }
        public Person(string name, DateTime birth, DateTime? death)
        {
            this.birth = birth;
            this.death = death;
            this.name = name;
        }
    }
}

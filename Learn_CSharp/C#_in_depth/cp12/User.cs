﻿using System.ComponentModel;

namespace CP12
{
    public partial class User
    {
        public string Name { get; set; }
        public int UserID { get; set; }
        public UserType UserType { get; set; }

        public User(string name, UserType userType)
        {
            Name = name;
            UserType = userType;
        }
        
        public override string ToString()
        {
            return string.Format("User: {0} ({1})", Name, UserType);
        }
    }
}

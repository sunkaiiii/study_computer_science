using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class MessageFactory
    {
        internal string Create(string username)
        {
            return username + "client is created";
        }
    }
}

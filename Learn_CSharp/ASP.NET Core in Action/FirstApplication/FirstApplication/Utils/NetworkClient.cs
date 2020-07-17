using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class NetworkClient
    {
        private readonly EmailServiceSettings _settings;
        public NetworkClient(EmailServiceSettings settings)
        {
            _settings = settings;
        }
        internal void SendEmail(string email)
        {
            Console.WriteLine(email);
        }
    }
}

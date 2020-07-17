namespace FirstApplication.Utils
{
    public class EmailServiceSettings
    {
        private readonly string host;
        private readonly int port;

        public EmailServiceSettings(string host, int port)
        {
            this.host = host;
            this.port = port;
        }
    }
}
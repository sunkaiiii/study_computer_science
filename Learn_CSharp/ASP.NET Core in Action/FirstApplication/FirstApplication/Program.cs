using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace FirstApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            CreateHostBuilder(args).Build().Run();
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureAppConfiguration(AddAppConfiguration)
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>();
                });

        private static void AddAppConfiguration(HostBuilderContext hostingContext, IConfigurationBuilder config)
        {
            //Loading from multiple providers
            config.AddJsonFile("sharedSettings.json", optional: true)
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange:true)  //rebuilt if the appsettings.json file changes
                .AddEnvironmentVariables();
        }
    }
}

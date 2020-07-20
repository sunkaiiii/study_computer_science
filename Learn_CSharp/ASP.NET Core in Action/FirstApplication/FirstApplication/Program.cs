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
            var env = hostingContext.HostingEnvironment; // the current IHostingEnvironment is available on the contex
            //Loading from multiple providers
            config.AddJsonFile("sharedSettings.json", optional: true)
                .AddJsonFile("appsettings.json", optional: false, reloadOnChange:true)  //rebuilt if the appsettings.json file changes
                .AddJsonFile($"appsettings.{env.EnvironmentName}.json",optional:true) //add an optional environment specific JSON file where the filename varies with the environment
                .AddEnvironmentVariables();
        }
    }
}

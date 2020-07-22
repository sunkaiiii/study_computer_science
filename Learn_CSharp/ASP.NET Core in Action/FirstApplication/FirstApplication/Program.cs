using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Serilog;

namespace FirstApplication
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Log.Logger = new LoggerConfiguration().WriteTo.Console().CreateLogger();
            try {
                CreateHostBuilder(args).Build().Run();
            }catch(Exception ex)
            {
                Log.Fatal(ex, "Host terminated unpectedly");
            }finally
            {
                Log.CloseAndFlush();
            }
            
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureAppConfiguration(AddAppConfiguration)
            .ConfigureLogging((ctx, builder) =>
            {
                builder.AddConfiguration(ctx.Configuration.GetSection("Logging")); //loads log filtering configuration from the logging section 
                builder.AddSeq();
            })
                .ConfigureLogging(buildder => buildder.AddConsole().AddFile()) //Add new providers with the configureLogging extension method
            .UseSerilog() //Registers the SerilogLoggerFactory and connects the Log.Logger as the sole logging provider
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>();
                });

        private static void AddAppConfiguration(HostBuilderContext hostingContext, IConfigurationBuilder config)
        {
            var env = hostingContext.HostingEnvironment; // the current IHostingEnvironment is available on the contex
            //Loading from multiple providers
            config.AddJsonFile("sharedSettings.json", optional: true)
                .AddJsonFile("hosting.json") //load configuration from the file to change the url
                .AddJsonFile("appsettings.json", optional: false, reloadOnChange:true)  //rebuilt if the appsettings.json file changes
                .AddJsonFile($"appsettings.{env.EnvironmentName}.json",optional:true) //add an optional environment specific JSON file where the filename varies with the environment
                .AddEnvironmentVariables();
        }
        public static IConfiguration GetLaunchConfiguration() => new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("hosting.json").Build();
    }
}

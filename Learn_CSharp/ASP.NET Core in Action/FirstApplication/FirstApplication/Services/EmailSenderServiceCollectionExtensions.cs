using FirstApplication.Controllers;
using FirstApplication.Utils;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Services
{
    public static class EmailSenderServiceCollectionExtensions
    {
        public static IServiceCollection AddEmailSender(this IServiceCollection services)
        {
            //providing object instances to container
            services.AddScoped<IEmailSender, EmailSender>();
            services.AddSingleton<NetworkClient>();
            services.AddScoped<MessageFactory>();
            services.AddSingleton(new EmailServiceSettings(host: "asd.asd.asd", port: 2555));
            services.AddSingleton<ISignInService,SignInSerivce>();
            return services;
        }
    }
}

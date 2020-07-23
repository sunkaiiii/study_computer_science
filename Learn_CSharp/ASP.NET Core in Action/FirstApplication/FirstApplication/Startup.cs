using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using FirstApplication.Controllers;
using FirstApplication.Entities;
using FirstApplication.Filters;
using FirstApplication.Middleware;
using FirstApplication.Services;
using FirstApplication.Utils;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

namespace FirstApplication
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllersWithViews();
            services.AddEmailSender(); //call the extension method

            //every time will create a new one
            //services.AddTransient<DataContext>();
            //services.AddTransient<Repository>();

            //this will use same instance for each request
            services.AddScoped<DataContext>();
            services.AddScoped<Repository>();
            services.AddSingleton<RecipeService>();
            var connectString = Configuration.GetConnectionString("DefaultConnection");
            services.AddDbContext<AppDbContext>(options =>
            {
                options.UseSqlServer(connectString); //specify the database provider in the customization options
            });
            services.AddMvc(options =>
            {
                //options.Filters.Add<LogResourceFilter>(); //add filter globally 
            });
            services.AddIdentity<IdentityUser, IdentityRole>(options => options.Password.RequiredLength = 10) //inject identity
                .AddDefaultTokenProviders()
                .AddEntityFrameworkStores<AppDbContext>();
            //services.AddTransient<IEmailSender, AuthMessageSender>();
            //services.AddTransient<ISmsSender, AuthMessageSender>();
            services.AddCors(options =>
            {
                options.AddPolicy("AllowShoppingApp", policy => policy.WithOrigins("http://shopping.com").AllowAnyMethod()); //Configureing a CORS policy to allow requests from a specific origin
            });
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            app.UseWelcomePage("/");
            //handle excetpion
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
            }
            //app.UseStatusCodePages(); //handle HTTP code error
            app.UseStatusCodePagesWithReExecute("/error/{0}"); //more typical way to handle the code
            app.UseRouting();
            app.UseStaticFiles();
            app.UseAuthentication();
            app.UseCors("AllowShoppingApp"); //Adds CORS middleware and uses AllowShopping App as the default policy
            // app.Map("/ping", branch => //using the map extension to create branching middleware pipeline
            //{
            //    branch.Run(async (context) =>
            //    {
            //        context.Response.ContentType = "text/plain";
            //        await context.Response.WriteAsync("pong");
            //    });
            //});
            app.Use(async (context, next) => //Using the Use method tor replace the Map method
            {
                if (context.Request.Path.StartsWithSegments("/ping"))
                {
                    context.Response.ContentType = "text/plain";
                    await context.Response.WriteAsync("pong");
                }
                else
                {
                    await next();
                }
            });

            app.UseMiddleware<HeadersMiddleware>(); //add headers to a response using custom component

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllerRoute(
                    name: "start_checkout",
                    pattern: "checkout",
                    defaults: new { controller = "Payment", action = "StartProcess" }); //define default controller and action for a specific url
                endpoints.MapControllerRoute(
                    name: "view_currency",
                    pattern: "{currency}/convert/{*others}", //pattern consists of a parameter for currency, a literal segment, and a catch-all parameter
                    constraints: new {currency=new LengthRouteConstraint(3)},
                    defaults: new { controller = "Currencies", action = "View" }); //multiple routes with anonymous types
                endpoints.MapControllerRoute(
                    name: "default",
                    pattern: "{controller=Home}/{action=Index}/{id?}"); //define global convention pattern
                
            });
       }
        
    }
}

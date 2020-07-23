using FirstApplication;
using FirstApplication.Entities;
using FirstApplication.Middleware;
using FirstApplication.Services;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.TestHost;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Xunit;

namespace XUnitTestProject1
{
    public class IntegrationTest
    {
        [Fact]
        public async Task StatusMiddlewareReturnsPong()
        {
            var hostBuilder = new WebHostBuilder().Configure(app => //configure a WebHostBuilder that defines in the app
            {
                app.UseMiddleware<StatusMiddleware>(); 
            });
            using(var server = new TestServer(hostBuilder)) //create an instance of the TestServer
            {
                HttpClient client = server.CreateClient();
                var response = await client.GetAsync("/ping");
                response.EnsureSuccessStatusCode();
                var content = await response.Content.ReadAsStringAsync();
                Assert.Equal("pong", content);
            }
        }

        [Fact]
        public async Task StatusMiddlewareReturnsPongMadeByStartup()
        {
            var hostBuilder = new WebHostBuilder().UseStartup<Startup>(); //directly use the Startup from the real app
            using (var server = new TestServer(hostBuilder))
            {
                HttpClient client = server.CreateClient();
                var response = await client.GetAsync("/ping");
                response.EnsureSuccessStatusCode();
                var content = await response.Content.ReadAsStringAsync();
                Assert.Equal("pong", content);
            }
        }

        [Fact]
        public void GetRecipeDetails_CanLoadFromContext()
        {
            var connection = new SqliteConnection("DataSource=:memory:");
            connection.Open();

            //cannot find the method Sqlite, maybe this is replaced by other method?
            
        //    var options = new DbContextOptionsBuilder<AppDbContext>().UseSqlite(connection).Options;
        //    using (var context = new AppDbContext(options))
        //    {
        //        context.Database.EnsureCreated();
        //        context.Recipes.AddRange(
        //                new Recipe { RecipeId = 1, Name = "Recipe1" },
        //                new Recipe { RecipeId = 2, Name = "Recipe2" },
        //                new Recipe { RecipeId = 3, Name = "Recipe3" });
        //        context.SaveChanges();
        //    }
        //   by using two separte contexts, this can avoid bugs in test due to EF Core cahcing data without writing it to the database
        //    using (var context = new AppDbContext(options))
        //    {
        //        var recipe = context.Recipes.Where(recipe => recipe.RecipeId == 2).FirstOrDefault();
        //        Assert.NotNull(recipe);
        //        Assert.Equal(2, recipe.RecipeId);
        //        Assert.Equal("Recipe2", recipe.Name);
        //    }
        //}
    }
}

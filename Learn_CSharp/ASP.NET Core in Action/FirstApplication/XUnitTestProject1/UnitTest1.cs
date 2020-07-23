using FirstApplication.Controllers;
using FirstApplication.Middleware;
using FirstApplication.Utils;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.IO;
using System.Threading.Tasks;
using Xunit;

namespace XUnitTestProject1
{
    public class UnitTest1
    {
       [Fact] //marked as a test method
       public void ConvertToGdp_ConvertsCorrectly()
        {
            var converter = new CurrencyConverter();
            decimal value = 3;
            decimal rate = 1.5m;
            int dp = 4;
            decimal exptected = 2;
            var actual = converter.ConvertToGbp(value, rate, dp);
            Assert.Equal(exptected, actual);
        }
        [Theory]
        [InlineData(0, 3, 0)]
        [InlineData(3, 1.5, 2)]
        [InlineData(3.75, 2.5, 1.5)]
        public void ConvertToGdp_ConvertsCorrectly_2(decimal value, decimal rate, decimal exptected)
        {
            var converter = new CurrencyConverter();
            int dps = 4;
            var actual = converter.ConvertToGbp(value, rate, dps);
            Assert.Equal(exptected, actual);
        }

        [Fact]
        public void ThrowsExceptionIfRateIsZero()
        {
            var converter = new CurrencyConverter();
            const decimal value = 1;
            const decimal rate = 0;
            const int dp = 2;
            var ex = Assert.Throws<ArgumentException>(
             () => converter.ConvertToGbp(value, rate, dp)); //exptect to throw an exception
        }

        [Fact]
        public async Task ForNonMatchingRequest_CallsNextDelegate()
        {
            var context = new DefaultHttpContext(); //Creates a DefaultHttpContext and sets the path for the request
            context.Request.Path = "/somepaths";
            var wasExecuted = false; //tracks wheter the RequestDelegate was executed
            RequestDelegate next = (ctx) =>
            {
                wasExecuted = true;
                return Task.CompletedTask;
            };
            var middelware = new StatusMiddleware(next: next);
            await middelware.Invoke(context);
            Assert.True(wasExecuted);
;        }

        [Fact]
        public async Task ReturnsPongBodyContent() //using testing StatusMiddleware when a matching Path is provided
        {
            var bodyStream = new MemoryStream(); //to read Body with memory stream
            var context = new DefaultHttpContext();
            context.Response.Body = bodyStream;
            context.Request.Path = "/ping";

            RequestDelegate next = (ctx) => Task.CompletedTask;
            var middleware = new StatusMiddleware(next);
            await middleware.Invoke(context);
            string response;
            bodyStream.Seek(0, SeekOrigin.Begin);
            using(var stringReader = new StreamReader(bodyStream))
            {
                response = await stringReader.ReadToEndAsync();
            }
            Assert.Equal("pong", response);
            Assert.Equal("text/plain", context.Response.ContentType);
            Assert.Equal(200, context.Response.StatusCode);
        }

        [Fact]
        public void Index_ReturnsIndexViewModelInViewResult()
        {
            var controller = new FruitController();
            IActionResult result = controller.View(2);
            Assert.IsType<OkObjectResult>(result);

        }
    }


}

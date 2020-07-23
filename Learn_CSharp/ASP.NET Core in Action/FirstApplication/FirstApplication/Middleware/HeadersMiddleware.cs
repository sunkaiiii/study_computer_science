using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Middleware
{
    public class HeadersMiddleware
    {
        private readonly RequestDelegate _next;
        public HeadersMiddleware(RequestDelegate next)
        {
            _next = next;
        }
        public async Task Invoke(HttpContext context) //the invoke mthod is called with HttpContext when a request is received
        {
            context.Response.OnStarting(() =>
            {
                context.Response.Headers["Strict-Transport-Security"] = "max-age=60";
                return Task.CompletedTask;
            });
            await _next(context);
        }
    }
}

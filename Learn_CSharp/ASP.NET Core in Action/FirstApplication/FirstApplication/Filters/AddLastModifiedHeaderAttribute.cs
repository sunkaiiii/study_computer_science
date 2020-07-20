using FirstApplication.Entities;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Filters
{
    public class AddLastModifiedHeaderAttribute:ResultFilterAttribute
    {
        public override void OnResultExecuting(ResultExecutingContext context)
        {
            if(context.Result is OkObjectResult result && result.Value is Recipe detail)
            {
                context.HttpContext.Response.GetTypedHeaders().LastModified = DateTimeOffset.Now;
            }
        }
    }

}

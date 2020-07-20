using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Filters
{
    public class HandleExceptionAttribute:ExceptionFilterAttribute
    {
        //use exception filter to build a custom object to return in the response
        public override void OnException(ExceptionContext context)
        {
            var error = new
            {
                Success = false,
                Errors = new[] { context.Exception.Message }
            };
            context.Result = new ObjectResult(error)
            {
                StatusCode = 500
            };
        context.ExceptionHandled = true;
        }
    }
}

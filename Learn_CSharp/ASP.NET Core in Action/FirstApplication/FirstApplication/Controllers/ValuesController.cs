using System;
using Microsoft.AspNetCore.Diagnostics;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    //Disabling StatusCodePagesMiddleware in a web API controller
    public class ValuesController:Controller
    {
        public string Index()
        {
            var statusCodePagesFeature = HttpContext.Features.Get<IStatusCodePagesFeature>(); //Try to get code from HTTPContext
            if (statusCodePagesFeature != null)
            {
                statusCodePagesFeature.Enabled = false; //Disable the feature for this request
            }
            return StatusCode(500).ToString(); //Return a 500 errcoide
        }
    }
}

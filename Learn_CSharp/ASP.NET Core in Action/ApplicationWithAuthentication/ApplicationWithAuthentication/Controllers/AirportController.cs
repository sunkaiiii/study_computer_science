using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace ApplicationWithAuthentication.Controllers
{
    public class AirportController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        [Authorize("CanEnterSecurity")]
        public IActionResult AirportSecurity()
        {
            return View();
        }

        [Authorize("CanAccessLounge")]
        public IActionResult AirportLounge()
        {
            return View();
        }
    }
}

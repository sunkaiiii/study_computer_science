using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using FirstApplication.Models;
using Microsoft.Extensions.Options;
using FirstApplication.Utils;

namespace FirstApplication.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger, IOptions<HomePageSetting> options, IOptionsSnapshot<HomePageSetting>optionsSnapshot)
        {
            _logger = logger;
            //the difference between IOptions and IOptionsSnapshot is IOptions is singleton, while IOptionsSnapshot is created when it is needed.
            Console.WriteLine(options.Value.Title);
            Console.WriteLine(optionsSnapshot.Value.Title); 
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        //an action requried pamameters
        public IActionResult Search(SearchModel searchModel)
        {
            if(ModelState.IsValid)
            {
                var viewModel = "do some search";
                return View(viewModel);
            }

            return Redirect("/");
        }
    }
}

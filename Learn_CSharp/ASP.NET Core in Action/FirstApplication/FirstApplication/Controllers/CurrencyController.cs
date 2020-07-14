using System;
using FirstApplication.Models;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class CurrencyController:Controller
    {
        public IActionResult Index()
        {
            var url = Url.Action(nameof(View), "Currency", new { code = "USD" }); //generating URLs based on an action
            return Content(string.Format("The URL is {0}",url));
        }

        public IActionResult Generating()
        {
            var url = Url.RouteUrl("view_currency", new { code = "GBP" }); //name of the route to use
            return Content(string.Format("The URL is {0}", url));
        }

        public IActionResult RedirectingToAnActionMethod()
        {
            return RedirectToAction(nameof(View), "Currency", new { id = 5 });
        }

        public IActionResult RedirectingToARoute()
        {
            return RedirectToRoute("view_currency", new { code = "GBP" });
        }

        public IActionResult View(string code)
        {
            return Content(code);
        }

        public IActionResult Checkout(UserBindingModel model) //binding with a complex model
        {
            return Content(model.ToString());
        }
    }
}

using System;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class CalculatorController : Controller
    {
        public IActionResult Square(int value) //the method parameter is the binding model
        {
            var result = value * value;
            return View(result);
        }

        public IActionResult ConvertCurrency(string currencyIn, string currencyOut, int qty)
        {
            return View(currencyIn + currencyOut + qty);
        }


    }
}

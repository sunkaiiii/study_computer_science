using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FirstApplication.Models;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace FirstApplication.Controllers
{
    public class ToDoController : Controller
    {
       public IActionResult Index()
        {
            ViewData["Message"]="You ToDo List"; //use view data to pass message`
            var viewModel = new ToDoItemViewModel
            {
                Title = "Tasks for today",
                Tasks = new List<String>
                {
                    "Get fuel",
                    "Check oil",
                    "Check type pressure"
                }
            };
            return View(viewModel); //create a ViewResult that looks for a view called view to do, pass the model
        }
    }
}

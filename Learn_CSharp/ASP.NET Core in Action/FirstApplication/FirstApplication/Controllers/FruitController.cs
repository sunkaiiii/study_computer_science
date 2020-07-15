using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace FirstApplication.Controllers
{
    public class FruitController : Controller
    {
        List<string> _fruit = new List<string>
        {
        "Pear",
        "Lemon",
        "Peach"
        };
        public IEnumerable<string> Index()
        {
            return _fruit;
        }

        public IActionResult View(int id)
        {
            if(id>=0 && id < _fruit.Count)
            {
                return Ok(_fruit[id]);
            }
            return NotFound();
        }

        [Route("{controller}/getFruit/{fruitId=0:int}")] //set default value
        public IActionResult getFruit(int fruitId)
        {
            return View(fruitId);
        }
    }
}

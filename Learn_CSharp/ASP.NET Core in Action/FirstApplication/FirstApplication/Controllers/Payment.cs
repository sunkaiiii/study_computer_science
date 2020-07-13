using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class Payment: Controller
    {
        public ActionResult<List<String>> StartProcess()
        {
            List<String> lists = new List<string>
            {
                "1"
            };
            return lists;
        }

        public ActionResult<string> Login()
        {
            return "123"; 
        }

        //for POST request only
        [HttpPost]
        public ActionResult<string> Login(String name,String password)
        {
            return "123";
        }
    }
}

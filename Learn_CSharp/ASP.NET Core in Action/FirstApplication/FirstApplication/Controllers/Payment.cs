using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Cors;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    [EnableCors("AllowShoppingApp")] //Applies CORS policy to every action method
    public class Payment: Controller
    {
        [EnableCors("AllowAnyOrigin")] //applies CORS policy to the action
        public ActionResult<List<String>> StartProcess()
        {
            List<String> lists = new List<string>
            {
                "1"
            };
            return lists;
        }

        [DisableCors] //disable the CORS policy, this only disable the policy which is attributed but not middleware
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

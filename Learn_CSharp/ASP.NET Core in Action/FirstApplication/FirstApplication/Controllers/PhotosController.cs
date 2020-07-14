using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class PhotosController:Controller
    {
        public IActionResult TagPhotosWithUser([FromHeader] string userId,[FromBody]List<string> photos) //the user id will bounded from an HTTP header
        {
            return Content(photos.ToString());
        }
    }
}

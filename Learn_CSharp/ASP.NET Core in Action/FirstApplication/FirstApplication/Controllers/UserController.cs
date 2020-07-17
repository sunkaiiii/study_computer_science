using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FirstApplication.Utils;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class UserController : Controller
    {
        private readonly IEmailSender _emailSender; //instead of creating the dependencies implicitly, inject via constructor
        public UserController(IEmailSender emailSender)
        {
            _emailSender = emailSender;
        }
        public IActionResult RegisterUser(string username)
        {
            _emailSender.SendEmail(username);
            return View();
        }

        public IActionResult SignInUser([FromServices]ISignInService signInService, string userName, string password) //service is resolved from the DI container nad injected as a parameter
        {
            signInService.singIn(userName, password);
            return View();
        }
    }

    public interface ISignInService
    {
        void singIn(string userName, string password);
    }

    public class SignInSerivce : ISignInService
    {
        public void singIn(string userName, string password)
        {
            Console.WriteLine(userName+" "+password);
        }
    }

    public class EmailSender:IEmailSender
    {
        private readonly NetworkClient _client;
        private readonly MessageFactory _facotry;
        public EmailSender(MessageFactory messageFactory, NetworkClient client)
        {
            _facotry = messageFactory;
            _client = client;
        }
        public void SendEmail(string username)
        {
            var email = _facotry.Create(username);
            _client.SendEmail(email);
            Console.WriteLine(username);
        }
    }

    public interface IEmailSender
    {
        public void SendEmail(string username);
    }
}

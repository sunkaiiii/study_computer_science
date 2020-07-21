using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ApplicationWithAuthentication.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace ApplicationWithAuthentication.Controllers
{
    public class RecipeController : Controller
    {
        private IAuthorizationService _authService;
        public RecipeController(IAuthorizationService service)
        {
            _authService = service;
        }
        public async Task<IActionResult> Index()
        {
            var recipe = new RecipeDetailViewModel();
            var authResult = await _authService.AuthorizeAsync(User, recipe, "CanManageRecipe");
            recipe.CanEditRecipe = authResult.Succeeded;
            return View(recipe);
        }
        
        [Authorize]
        public async Task<IActionResult> Edit(int id)
        {
            int recipe = 1;
            var authResult = await _authService.AuthorizeAsync(User, recipe, "CanManageRecipe"); //providing Claims, resource and policyname
            if(!authResult.Succeeded)
            {
                return new ForbidResult();
            }
            return View(recipe);
        }
    }
}

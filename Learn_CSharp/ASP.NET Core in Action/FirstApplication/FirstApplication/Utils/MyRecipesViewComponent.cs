using FirstApplication.Services;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class RecipesViewComponent:ViewComponent //Deriving from the ViewComponent base class
    {
        private readonly RecipeService _recipeService;
        private readonly UserManager<IdentityUser> _userManager;
        public RecipesViewComponent(RecipeService recipeService,
UserManager<IdentityUser> userManager)
        {
            _recipeService = recipeService;
            _userManager = userManager;
        }

        public async Task<IViewComponentResult> InvokeAsync(int numberOfRecipes)
        {
            if (!User.Identity.IsAuthenticated)
            {
                return View();
                //return View("Unauthenticated");
            }
            var userId = _userManager.GetUserId(HttpContext.User);
            var recipes = await _recipeService.GetRecipesForUser(
            userId, numberOfRecipes);
            return View(recipes);
        }
    }
}

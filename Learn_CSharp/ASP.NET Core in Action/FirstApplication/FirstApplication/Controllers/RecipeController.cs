using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using FirstApplication.Entities;
using FirstApplication.Filters;
using FirstApplication.Models;
using FirstApplication.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;

namespace FirstApplication.Controllers
{
    [ValidateModel, HandleException,FeatureEnable(IsEnabled =true)]
    public class RecipeController : Controller
    {
        readonly AppDbContext _context;
        readonly RecipeService _service;
        private readonly ILogger _log;
        public RecipeController(AppDbContext context, RecipeService service, ILogger<RecipeController> log) //inject service and ILogger
        {
            _context = context;
            _service = service;
            _log = log;
        }
        public int CreateRecipe(CreateRecipeCommand cmd)
        {
            var recipe = new Recipe
            {
                Name = cmd.Name,
                TimeToCook = new TimeSpan(100),
                Method = cmd.Method,
                Ingredients = cmd.Ingredients?.Select(i => new Ingredient { Name = i.Name, Quantity = i.Quantity, Unit = i.Unit }).ToList()
            };
            _context.Add(recipe);
            _context.SaveChanges();
            return recipe.RecipeId;
        }

        public ICollection<Recipe> GetRecipes()
        {
           var recipe = _context.Recipes.Where(r => r.IsDeleted).ToList();
            _log.LogInformation("Loaded {RecipeList} recipes", recipe.Count);
            return recipe;
        }

        public ActionResult<Recipe> GetRecipe(int id)
        {
            return _context.Recipes.Where(x => x.RecipeId == id).SingleOrDefault();
        }

        [HttpGet("{controller}/Get/{id}"), EnsureRecipeExists, AddLastModifiedHeader]
        public IActionResult Get(int id)
        {
            _log.LogInformation("getID called");
            return Ok(id);
        }

        [Authorize, EnsureRecipeExists]
        [HttpPost("{controller}/Edit/{id}")]
        public IActionResult Edit(int id, [FromBody]Recipe recipe)
        {
            return Ok();
        }
    }
}

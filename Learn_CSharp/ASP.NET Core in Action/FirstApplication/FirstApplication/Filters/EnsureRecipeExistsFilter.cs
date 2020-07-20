using FirstApplication.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Filters
{
    public class EnsureRecipeExistsFilter:IActionFilter
    {
        private readonly RecipeService _service;
        public EnsureRecipeExistsFilter(RecipeService service)
        {
            _service = service;
        }

        public void OnActionExecuted(ActionExecutedContext context)
        {
            throw new NotImplementedException();
        }

        public void OnActionExecuting(ActionExecutingContext context)
        {
            var recipeId = (int)context.ActionArguments["id"];
            if (!_service.DoesRecipeExist(recipeId))
            {
                context.Result = new NotFoundResult();
            }
        }
    }
}

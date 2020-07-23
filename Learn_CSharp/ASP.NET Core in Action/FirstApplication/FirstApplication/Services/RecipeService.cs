using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Services
{
    public class RecipeService
    {
        internal bool DoesRecipeExist(int recipeId)
        {
            return recipeId % 2 == 0; //some dummy judgement
        }

        internal async Task<bool> GetRecipesForUser(string userId, int numberOfRecipes)
        {
            return await Task.Run(() =>
            {
                return DateTime.Now.Second % 2 == 0;
            });
        }
    }
}

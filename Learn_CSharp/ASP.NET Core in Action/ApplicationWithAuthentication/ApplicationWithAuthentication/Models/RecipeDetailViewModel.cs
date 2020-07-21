using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationWithAuthentication.Models
{
    public class RecipeDetailViewModel
    {
        public string Id { get; set; }
        public string Content { get; set; }
        public bool CanEditRecipe { get; set; }
    }
}

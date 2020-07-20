using FirstApplication.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Models
{
    public class CreateRecipeCommand
    {
        public string Name { get; set; }
        public string Method { get; set; }
        public List<Ingredient>? Ingredients { get; set; }
    }
}

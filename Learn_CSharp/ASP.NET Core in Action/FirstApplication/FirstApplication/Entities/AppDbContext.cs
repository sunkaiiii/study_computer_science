using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Entities
{
    public class AppDbContext:DbContext
    {
        public DbSet<Recipe> Recipes { get; set; }
        public AppDbContext(DbContextOptions<AppDbContext> options)
: base(options) { }
    }
}

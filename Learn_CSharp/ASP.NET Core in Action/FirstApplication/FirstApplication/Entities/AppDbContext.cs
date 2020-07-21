using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Entities
{
    public class AppDbContext:IdentityDbContext<IdentityUser>
    {
        public DbSet<Recipe> Recipes { get; set; }
        public AppDbContext(DbContextOptions<AppDbContext> options)
: base(options) { }
    }
}

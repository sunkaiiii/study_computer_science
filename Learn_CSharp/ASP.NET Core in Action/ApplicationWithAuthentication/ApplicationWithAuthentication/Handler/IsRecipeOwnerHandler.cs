using ApplicationWithAuthentication.Models;
using ApplicationWithAuthentication.Requirements;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationWithAuthentication.Handler
{
    //the interface is diffrent to the previous handler
    public class IsRecipeOwnerHandler:AuthorizationHandler<IsRecipeOwnerRequirement,Recipe>
    {
        private readonly UserManager<IdentityUser> userManager;
        public IsRecipeOwnerHandler(UserManager<IdentityUser> userManager)
        {
            this.userManager = userManager;
        }
        protected override async Task HandleRequirementAsync(AuthorizationHandlerContext context, IsRecipeOwnerRequirement requirement, Recipe resource)
        {
            var appUser = await userManager.GetUserAsync(context.User);
            if (appUser == null)
                return;
            if(resource.Id.Equals(appUser.Id))
            {
                context.Succeed(requirement);
            }
        }
    }
}

using ApplicationWithAuthentication.Requirements;
using Microsoft.AspNetCore.Authorization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationWithAuthentication.Handler
{
    public class FrequentFlyerHandler:AuthorizationHandler<AllowedInLoungeRequirement>
    {
        //Check whether the user has the FrequentFlyerClass claim with the Gold value
        protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, AllowedInLoungeRequirement requirement)
        {
            if(context.User.HasClaim("FrequentFlyerClass","Gold"))
            {
                context.Succeed(requirement);
            }
            return Task.CompletedTask;
        }
    }
}

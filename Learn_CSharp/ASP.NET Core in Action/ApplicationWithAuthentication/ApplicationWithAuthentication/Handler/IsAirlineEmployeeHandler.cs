using ApplicationWithAuthentication.Requirements;
using Microsoft.AspNetCore.Authorization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationWithAuthentication.Handler
{
    public class IsAirlineEmployeeHandler:AuthorizationHandler<AllowedInLoungeRequirement>
    {
        protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, AllowedInLoungeRequirement requirement)
        {
            if(context.User.HasClaim(c=>c.Type=="IsBanned"))
            {
                context.Fail();
            }
            else if(context.User.HasClaim(c=>c.Type=="EmployeeNumber"))
            {
                context.Succeed(requirement);
            }
            return Task.CompletedTask;
        }
    }
}

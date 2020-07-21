using Microsoft.AspNetCore.Authorization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ApplicationWithAuthentication.Requirements
{
    //An identity requirement
    public class MinimumAgeRequirement:IAuthorizationRequirement
    {
        public int MinimumAge { get; }
        public MinimumAgeRequirement(int minimumAge)
        {
            MinimumAge = minimumAge;
        }
    }
}

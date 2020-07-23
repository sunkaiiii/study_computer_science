using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class CurrencyCodeAttribute:ValidationAttribute //Derives from ValidationAttribute to ensure your attribute is used during validation
    {
        private readonly string[] _allowedCodes;
        public CurrencyCodeAttribute(params string[] allowedCodes) //the attribute takes in an array of allowed currency codes.
        {
            _allowedCodes = allowedCodes;
        }

        protected override ValidationResult IsValid(
 object value, ValidationContext context)
        {
            var code = value as string;
            if (code == null || !_allowedCodes.Contains(code))
            {
                return new ValidationResult("Not a valid currency code");
            }
            return ValidationResult.Success;
        }
    }
}

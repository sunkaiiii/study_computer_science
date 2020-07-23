using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FirstApplication.Utils
{
    public class CurrencyConverter //class that needs to be tested
    {
        public decimal ConvertToGbp(
                decimal value, decimal exchangeRate, int decimalPlaces)
        {
            if (exchangeRate <= 0)
            {
                throw new ArgumentException(
                "Exchange rate must be greater than zero",
                nameof(exchangeRate));
            }
            var valueInGbp = value / exchangeRate;
            return decimal.Round(valueInGbp, decimalPlaces);
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter12
{
    public static class DatetimeUtils
    {
        //使用扩展方法分解DateTime
        public static void Deconstruct(
            this DateTime dateTime,
            out int year, out int month, out int day) =>
            (year, month, day) =
            (dateTime.Year, dateTime.Month, dateTime.Day);
    }
}

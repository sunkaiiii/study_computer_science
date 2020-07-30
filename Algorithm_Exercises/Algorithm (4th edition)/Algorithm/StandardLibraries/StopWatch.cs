using System;
namespace StandardLibraries
{
    public class StopWatch
    {
        private readonly long start;
        private static readonly DateTime Jan1st1970 = new DateTime
    (1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
        public StopWatch()
        {
            start = CurrentTimeMillis;
        }

        public double ElapsedTime => (CurrentTimeMillis - start) / 1000.0;

        public static long CurrentTimeMillis => (long)(DateTime.UtcNow - Jan1st1970).TotalMilliseconds;
    }
}

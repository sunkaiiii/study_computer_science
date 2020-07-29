using System;
namespace StandardLibraries
{
    public class StopWatch
    {
        private readonly int start;
        private static readonly DateTime Jan1st1970 = new DateTime
    (1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
        public StopWatch()
        {
            start = CurrentTimeMillis;
        }

        public double ElapsedTime => (CurrentTimeMillis - start) / 1000.0;

        public static int CurrentTimeMillis => (int)(DateTime.UtcNow - Jan1st1970).TotalMilliseconds;
    }
}

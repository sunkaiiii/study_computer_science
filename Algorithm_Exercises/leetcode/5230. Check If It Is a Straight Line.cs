using System;

namespace ConsoleApp1
{
    class Program
    {
        //You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
        //        2 <= coordinates.length <= 1000
        //coordinates[i].length == 2
        //-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
        //coordinates contains no duplicate point.
        public bool CheckStraightLine(int[][] coordinates)
        {
            double x1 = coordinates[0][0];
            double x2 = coordinates[1][0];
            double y1 = coordinates[0][1];
            double y2 = coordinates[1][1];

            if (x2 - x1 == 0 || y2 - y1 == 0)
            {
                bool result = true;
                for (int i = 2; i < coordinates.Length && result; i++)
                {
                    if (x2 - x1 == 0)
                    {
                        if (coordinates[i][0] != x2)
                        {
                            result = false;
                        }
                    }
                    if (y2 - y1 == 0)
                    {
                        if (coordinates[i][1] != y2)
                        {
                            result = false;
                        }
                    }
                }
                return result;
            }

            Func<double, double> formula = (double x) => (((x - x1) / (x2 - x1)) * (y2 - y1) + y1);
            for (int i = 2; i < coordinates.Length; i++)
            {
                double y = formula(coordinates[i][0]);
                //Console.WriteLine(y+","+coordinates[i][1]);
                if (y - coordinates[i][1] > 0.001 || y - coordinates[i][1] < -0.001)
                {
                    //Console.WriteLine("wrong"+ y+","+coordinates[i][1]);
                    return false;
                }
            }
            return true;
        }
        static void Main(string[] args)
        {
            //CheckStraightLine();
            Console.WriteLine("Hello World!");
        }
    }
}

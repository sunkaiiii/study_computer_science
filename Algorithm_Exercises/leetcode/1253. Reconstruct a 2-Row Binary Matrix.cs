using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    class Program
    {
        //        Given the following details of a matrix with n columns and 2 rows :

        //The matrix is a binary matrix, which means each element in the matrix can be 0 or 1.
        //The sum of elements of the 0-th(upper) row is given as upper.
        //The sum of elements of the 1-st(lower) row is given as lower.
        //The sum of elements in the i-th column(0-indexed) is colsum[i], where colsum is given as an integer array with length n.
        //Input: upper = 5, lower = 5, colsum = [2,1,2,0,1,0,1,2,0,1]
        //Output: [[1,1,1,0,1,0,0,1,0,0],[1,0,1,0,0,0,1,1,0,1]]
        public IList<IList<int>> ReconstructMatrix(int upper, int lower, int[] colsum)
        {
            var result = new List<IList<int>>();
            int sum = 0;
            foreach (int i in colsum)
                sum += i;
            if (sum != upper + lower)
                return result;
            var upperList = new List<int>();
            var lowerList = new List<int>();
            foreach(int i in colsum)
            {
                if(upper>0 && i==2)
                {
                    upperList.Add(1);
                    lowerList.Add(1);
                    upper--;
                }
                else
                {
                    upperList.Add(0);
                    lowerList.Add(i);
                }
            }

            for(int i=0;upper>0;i++)
            {
                if(lowerList[i]>0&&upperList[i]==0)
                {
                    upperList[i] = 1;
                    lowerList[i] = 0;
                    upper--;
                }
            }
            result.Add(upperList);
            result.Add(lowerList);
            return result;
        }
        static void Main(string[] args)
        {
            var list = new int[] { 0, 1, 2, 0, 0, 0, 0, 2, 1, 2, 1, 2 };
            new Program().ReconstructMatrix(9, 2, list);
        }
    }
}

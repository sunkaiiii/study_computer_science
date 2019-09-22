//Write a program to find the n - th ugly number.
//
//Ugly numbers are positive integers which are divisible by a or b or c.
//Input: n = 3, a = 2, b = 3, c = 5
//	Output : 4
//	Explanation : The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10...The 3rd is 4.
//	Input : n = 4, a = 2, b = 3, c = 4
//	Output : 6
//	Explanation : The ugly numbers are 2, 3, 4, 6, 8, 9, 12...The 4th is 6.

#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;
int nthUglyNumber(int n, int a, int b, int c) {
	int timea = 0, timeb = 0, timec = 0;
	int result;
	for (int i = 1; i <= n; i++)
	{
		long ta = a * (timea + 1);
		long tb = b * (timeb + 1);
		long tc = c * (timec + 1);
		long tempresult = std::min(std::min(ta, tb), tc);
		if (tempresult == ta)
		{
			timea++;
		}
		if (tempresult == tb)
		{
			timeb++;
		}
		if (tempresult == tc)
		{
			timec++;
		}
		result = tempresult;
	}
	return result;
}


int main()
{
	std::cout << nthUglyNumber(3, 2, 3, 5)<<std::endl;
	std::cout << nthUglyNumber(4, 2, 3, 4) << std::endl;
	std::cout << nthUglyNumber(5, 2, 11, 13) << std::endl;
	std::cout << nthUglyNumber(1000000000, 2, 217983653, 336916467) << std::endl;
}
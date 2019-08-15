#include <iostream>
/*
Runtime: 4 ms, faster than 68.37% of C++ online submissions for Reverse Integer.
Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Reverse Integer.
*/

int reverse(int x) {
    int result=0;
    int overflowLimit=0x7fffffff/10;
    int overflowLimit2=-overflowLimit;
    while(x!=0)
    {
        if(result>overflowLimit||result<overflowLimit2)
            return 0;
        result=result*10+x%10;
        x/=10;
    } 
    return result;
}

int main()
{
    int a;
    std::cin>>a;
    std::cout<<reverse(a)<<std::endl;
}
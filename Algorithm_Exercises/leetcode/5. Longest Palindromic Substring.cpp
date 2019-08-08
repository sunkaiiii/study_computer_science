#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using std::string;
//Runtime: 16 ms, faster than 84.00% of C++ online submissions for Longest Palindromic Substring.
//Memory Usage: 8.8 MB, less than 84.62% of C++ online submissions for Longest Palindromic Substring.
void findPalindrome(string &s,int i,int j, int &len,int &left)
{
    while(i>=0&&j<s.size()&&s[i]==s[j])
    {
        i--;
        j++;
    }
    i++;
    j--;
    if(j-i+1>len)
    {
        len=j-i+1;
        left=i;
    }
}

string longestPalindrome(string s) {
    int n=s.length();
    if(n<2)
        return s;
    int left=0,len=0;
    for(int i=0;i<n;i++)
    {
        findPalindrome(s,i,i, len,left);
        if(i+1!=n&&s[i]==s[i+1]){
        findPalindrome(s, i, i+1, len,left);
        }
    }
    return s.substr(left,len);
}


int main() {
    string s;
    std::cin >> s;
    std::cout << longestPalindrome(s)<<std::endl;
}

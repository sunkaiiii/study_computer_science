/*
出栈顺序
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 32768K，其他语言 65536K
题目描述
已知某一个字母序列，把序列中的字母按出现顺序压入一个栈，在入栈的任意过程中，允许栈中的字母出栈，求所有可能的出栈顺序

输入描述:
字符串，如：abc
输出描述:
可能的出栈顺序，每行一种顺序
示例1
输入

abc
输出

abc
acb
bac
bca
cba
*/
#include<iostream>
#include<string>
#include<stack>
#include<deque>
using std::endl;
std::stack<std::string> result;
void print(std::stack<char> stack,std::string s,int index,int len,std::deque<char> q)
{
  if(len==index)
  {
    while(!stack.empty())
    {
      char c=stack.top();
      q.push_back(c);
      stack.pop();
    }
    std::string s2;
    while(!q.empty())
    {
      char c=q.front();
      q.pop_front();
      s2+=c;
    }
    result.push(s2);
    return;
  }
  stack.push(s[index]);
  print(stack,s,index+1,len,q);
  stack.pop();
  std::stack<char> s2;
  while(!stack.empty())
  {
    char c=stack.top();
    q.push_back(c);
    stack.pop();
    stack.push(s[index]);
    s2.push(c);
    print(stack,s,index+1,len,q);
    stack.pop();
  }
}
int main()
{
  std::string s;
  std::cin>>s;
  std::stack<char> stack;
  int len=s.size();
  std::deque<char> q;
  print(stack,s,0,len,q);
  while(!result.empty())
  {
    std::cout<<result.top()<<endl;
    result.pop();
  }
}

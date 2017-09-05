/*
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
class Solution
{
public:
    void push(int node) {
        while(!stack1.empty()){
          int s=stack1.top();
          stack1.pop();
          stack2.push(s);
        }
        stack1.push(node);
        while(!stack2.empty()){
          int s=stack2.top();
          stack2.pop();
          stack1.push(s);
        }
    }

    int pop() {
        if(!stack1.empty())
        {
          int s=stack1.top();
          stack1.pop();
          return s;
        }
        else
        {
          return NULL;
        }
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

int main(){
  Solution s;
  s.push(1);
  s.push(2);
  s.push(3);
  cout<<s.pop();
}

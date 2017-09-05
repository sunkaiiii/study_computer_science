/*
题目描述
输入一个链表，从尾到头打印链表每个节点的值。
*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
struct ListNode {
        int val;
       struct ListNode *next;
       ListNode(int x) :
            val(x), next(NULL) {
        }
  };
class Solution {
public:
    std::vector<int> printListFromTailToHead(ListNode* head) {
        std::vector<int> v;
        ListNode* p=head;
        do
        {
          v.push_back(p->val);
          p=p->next;
        }while(p!=NULL);
        std::reverse(v.begin(),v.end());
        return v;
    }
};

int main(){
  ListNode* p1=new ListNode(0);
  ListNode* p2=new ListNode(1);
  ListNode* p3=new ListNode(2);
  p1->next=p2;
  p2->next=p3;
  Solution s;
  std::vector<int> v=s.printListFromTailToHead(p1);
  for(std::vector<int>::iterator i=v.begin();i!=v.end();i++){
    std::cout<<*i<<" ";
  }
}

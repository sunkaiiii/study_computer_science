#include <iostream>

/*
 You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 
 You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 
 Example:
 
 Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 0 -> 8
 Explanation: 342 + 465 = 807.
 */

/*
 Runtime: 16 ms, faster than 98.29% of C++ online submissions for Add Two Numbers.
 Memory Usage: 9.7 MB, less than 97.81% of C++ online submissions for Add Two Numbers.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    
};

ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
    ListNode* cur=l1;
    ListNode* first=cur;
    int offset=0;
    ListNode* buf=l2;
    do{
        int a=offset;
        ListNode* next;
        if(l1!=nullptr){
            a+=l1->val;
        }
        if(l2!=nullptr){
            a+=l2->val;
        }
        if(a>=10){
            cur->val=a%10;
            offset=1;
        }else{
            cur->val=a;
            offset=0;
        }
        if(l1!=nullptr){
            l1=l1->next;
        }
        if(l2!=nullptr){
            l2=l2->next;
        }
        next=l1==nullptr?l2:l1;
        if(next==nullptr&&a>=10){
            next=buf;
            buf->val=1;
            buf->next=nullptr;
        }
        cur->next=next;
        cur=next;
    }while(l1!=nullptr||l2!=nullptr);
    return first;
}

int main(){
    ListNode* l1=new ListNode(1);
//    ListNode* l2=new ListNode(4);
//    ListNode* l3=new ListNode(3);
    
    ListNode* l4=new ListNode(9);
    ListNode* l5=new ListNode(9);
//    ListNode* l6=new ListNode(4);
    
//    l1->next=l2;
//    l2->next=l3;
    l4->next=l5;
//    l5->next=l6;
    auto list=addTwoNumbers(l1, l4);
    do{
        std::cout<<list->val<<"->";
        list=list->next;
    }while(list!=nullptr);
    std::cout<<std::endl;
}

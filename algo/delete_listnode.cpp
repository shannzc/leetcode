#include <stdlib.h>
#include <vector>
#include <iostream>
#include<memory>
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int setval){val = setval; next = nullptr;}
    ListNode(){val = 0; next = nullptr;}
};

class listnode_lib
{
private:
    /* data */
public:
    ListNode *delete_value(ListNode *head, int value){     //删除链表中所有的value
        ListNode *leader = new ListNode(-1);
        leader->next = head;
        ListNode *cur = leader;
        while (cur->next != nullptr){
            if (cur->next->val == value){
                cur->next = cur->next->next;
            }else{
                cur = cur->next;
            }  
        }
        ListNode *return_ = leader->next;
        delete leader;
        return return_;
    }

    ListNode *reverse(ListNode *head){            //反转链表 ,快慢指针
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur != nullptr)
        {
            ListNode *tmp = nullptr;
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }

    ListNode *add_twolist(ListNode *one, ListNode *two){    //两数相加
        ListNode *Listsum = new ListNode(-1);
        ListNode *head = Listsum;
        bool jinwei = false;
        while (one != nullptr || two != nullptr){
            Listsum->next = new ListNode(-1);
            int sum = 0;
            if(one != nullptr && two != nullptr){
                sum = one->val + two->val + jinwei;
                if(sum >= 10){
                    jinwei = true;
                    Listsum->next->val = sum%10;
                }else{
                    jinwei = false;
                    Listsum->next->val = sum;
                }
            }else if (one != nullptr){
                Listsum->next->val = one->val + jinwei;
            }else if(two != nullptr){
                Listsum->next->val = two->val + jinwei;
            }
            Listsum = Listsum->next;
            one = one->next;
            two = two->next;
        }
        Listsum->next = jinwei ? new ListNode(1) : nullptr;
        return head->next; 
    }

    ListNode *delete_lastn(ListNode *head, size_t n){            //双指针，一趟循环让fast先走n步,删除倒数第N个节点
        ListNode *fast = head;
        ListNode *slow = head;
        size_t step = 0;
        while (fast->next != nullptr){
            if (step < n){
                fast = fast->next;
                step++;
            }else{
                fast = fast->next;
                slow = slow->next;
            }
        }
        slow->next = slow->next->next;
        return head;
    }

    ListNode *circle(ListNode *head){                //判断链表成环，并返回入口地址
        ListNode *first = head;
        ListNode *second = head;
        while (first != nullptr && first->next != nullptr)
        {
            second = second->next;
            first = first->next->next;
            if (first == second)
            {
                ListNode *third = head;
                while (third != first)
                {
                    third = third->next;
                    first = first->next;
                }
                return third; 
            }
            
        }
        return nullptr;
        
    }

    ListNode *switch_two_node(ListNode *head){               //两两交换链表节点
        ListNode *cur = new ListNode(-1);
        ListNode *handle = head;
        cur->next = head; 
        while (cur->next != nullptr && cur->next->next != nullptr)
        {
            ListNode *tmp = cur->next;
            ListNode *tmp2 = cur->next->next->next;
            cur->next = cur->next->next;
            cur->next->next = tmp;
            cur->next->next->next = tmp2;
            cur = cur->next->next;
        }
        return handle;
    }
};
int main(){
    int value_[] = {9,1,1,0,6,4,6,8,5};
    ListNode *intput = new ListNode(0);
    ListNode *point = intput;             //移动intput去赋值，用point作为链表头使用
    for(size_t i = 0; i < sizeof(value_)/sizeof(int); i++){
        intput->val = value_[i];
        if(i == sizeof(value_)/sizeof(int) -1){
            intput->next = nullptr;}
        else{
            intput->next = new ListNode(value_[i+1]);
            intput = intput->next;
        }   
    }
    std::shared_ptr<listnode_lib> solve = std::make_shared<listnode_lib>();
    // ListNode *result = solve->delete_value(point, 3);
    // ListNode *reverse_result = solve->reverse(point);
    // ListNode *add = solve->add_twolist(point, point);
    // ListNode *delete_lastn = solve->delete_lastn(point, 1);
    ListNode *result = solve->switch_two_node(point);
    printf("done");
}

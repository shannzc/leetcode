#include <stdlib.h>
#include <vector>
#include <stack>
#include <iostream>
struct binary_tree
{
    int val;
    // binary_tree *root;
    binary_tree *left;
    binary_tree *right;
    binary_tree():val(0), left(nullptr), right(nullptr){}
    binary_tree(int value):val(value), left(nullptr), right(nullptr){}
    binary_tree(int value, binary_tree *l, binary_tree *r):val(0), left(l), right(r){}
};

class middle
{
private:
    /* data */
public:
    std::vector<int> Solution(binary_tree *tree){            //中序遍历
        std::vector<int> contain;
        std::stack<binary_tree*> cup;
        cup.push(tree);
        while (!cup.empty()){
            if (cup.top() != nullptr) {
                binary_tree *tmp = cup.top();
                cup.pop();
                if(tmp->right) cup.push(tmp->right);    //右        前序，后续只需变更这三个顺序就行
                cup.push(tmp);                          //中
                cup.push(nullptr);
                if(tmp->left) cup.push(tmp->left);      //左
            }else{
                cup.pop();       //把null pop出去，下一个就是节点
                contain.push_back(cup.top()->val);
                cup.pop();
            }
        }
        return contain;
    }
};

int main(){

}

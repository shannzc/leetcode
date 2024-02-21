#include <stdlib.h>
#include <vector>
#include<stack>
#include <iostream>
template<typename T>
class twostack
{
private:
std::stack<T> first;
std::stack<T> second;
public:
    twostack(){};
    ~twostack(){};
    void push(T a){
        first.push(a);    
    };
    T pop(){
        if (second.size() != 0)
        {
            T temp = second.top();
            second.pop();
            return temp;
        }
        else if(first.size() != 0)
        {
            while (first.size() != 0)
            {
                second.push(first.top());
                first.pop();
            }
            T temp = second.top();
            second.pop();
            return temp;
        }
        
    };
};
 int main(){
    twostack<std::string> queue;
    queue.push("asdg");
    queue.push("llll");
    queue.push("rtyuuytre");
    std::cout << queue.pop() << std::endl;
 }


//  入队列正常push,每次出队列时先检测second不为空直接pop,否者将first全都移到second,再pop
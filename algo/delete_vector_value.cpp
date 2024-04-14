#include <stdlib.h>
#include <vector>
#include <iostream>

class delete_vector_value
{
private:
    /* data */
public:
    int removeElement(std::vector<int> &data, int val){          //删除数组中所有的val
        size_t slow = 0;
        for(size_t first = 0; first < data.size(); first++){
            if (data[first] != val){
                data[slow] = data[first];
                slow++;
            }   
            //  3 4  5 6 7 8 7 7 8 6 5
        }
        return slow;
    }
};

int main(){
    delete_vector_value demo;
    std::vector<int> data__{1,2,4,5,2,2,4,3,5,2,3,2,2,2};
    auto lenth = demo.removeElement(data__, 2);
    printf("after remove lenth is %d\n", lenth);
    // std::cout << data__ << std::endl;
}

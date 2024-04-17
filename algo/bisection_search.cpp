#include <stdlib.h>
#include <vector>
#include <cstdio>
// #include <iostream>
class bisection_search
{
public:
    int search(std::vector<int> &data, int target);
};
int bisection_search::search(std::vector<int> &data, int target){
    size_t left = 0;
    size_t right = data.size();
    while (left < right)                    //注意是左闭右开的区间 [  )
    {
        size_t middle = ((right + left) / 2);
        if (target < data[middle])
        {
            right = middle;
        }else if(target > data[middle]){
            left = middle + 1;             //middle已经比较过了，要加1
        }else{
            return middle;
        }
    }
    return -1;
}

int main(){
    bisection_search finder;
    std::vector<int> data_ = {1, 2, 3, 56, 65, 66, 88, 99, 123, 454};
    printf("location in data is %d\n", finder.search(data_, 36));
}

//前提是个有序数组
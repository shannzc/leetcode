#include <string>
#include <vector>

 class string_reverse
 {
 private:
    /* data */
 public:
    void reverse(std::string &str_){
        for (size_t i = 0, j = str_.size() - 1; i < str_.size() / 2; i++, j--)
        {
            std::swap(str_[i], str_[j]);
        }
        
    }
 };

int main(){
    std::string test = "ertyuuyjhgf";
    string_reverse reverse_;
    reverse_.reverse(test);
    printf(test.c_str());

    size_t num = 0;
    auto func = [&](){
        printf("buhuo is %d\n", num);
    };
    for(size_t i = 0; i < 8; i++){
        num++;
        func();
    }
    
}
 
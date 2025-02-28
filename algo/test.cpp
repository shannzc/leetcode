#include <memory>
饿汉式单例
class singlon
{
private:
    /* data */
    static singlon instance;
    singlon();
public:
    static singlon & get_instance(){
        return instance;
    }
    singlon(const singlon&) = delete;
    singlon& operator = (const singlon&) = delete;
};
懒汉式单例（线程不安全）
class singlon
{
private:
    /* data */
    static singlon* instance = nullptr;
    std::mutex mutable;
    singlon();
public:
    static singlon & get_instance(){
        std::lock_guard<std::mutex>lock mutable;
        if(instance == nullptr){
            singlon = new singlon();
        } 
        return singlon;
        
    }
    singlon(const singlon&) = delete;
    singlon& operator = (const singlon&) = delete;
};
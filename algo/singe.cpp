// 懒汉式单例（线程不安全）
#include <iostream>
#include <mutex>

class ThreadSafeLazySingleton {
private:
    static ThreadSafeLazySingleton* instance;
    static std::mutex mutex;
    ThreadSafeLazySingleton() {}

public:
    static ThreadSafeLazySingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex); // 加锁
            if (instance == nullptr) {
                instance = new ThreadSafeLazySingleton();
            }
        }
        return instance;
    }

    ThreadSafeLazySingleton(const ThreadSafeLazySingleton&) = delete;
    ThreadSafeLazySingleton& operator=(const ThreadSafeLazySingleton&) = delete;
};

ThreadSafeLazySingleton* ThreadSafeLazySingleton::instance = nullptr;
std::mutex ThreadSafeLazySingleton::mutex;

int main() {
    ThreadSafeLazySingleton* singleton = ThreadSafeLazySingleton::getInstance();
    std::cout << "Singleton address: " << singleton << std::endl;
    return 0;
}



// 懒汉式单例（线程安全）

#include <iostream>
#include <mutex>

class ThreadSafeLazySingleton {
private:
    static ThreadSafeLazySingleton* instance;
    static std::mutex mutex;
    ThreadSafeLazySingleton() {}

public:
    static ThreadSafeLazySingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex); // 加锁
            if (instance == nullptr) {
                instance = new ThreadSafeLazySingleton();
            }
        }
        return instance;
    }

    ThreadSafeLazySingleton(const ThreadSafeLazySingleton&) = delete;
    ThreadSafeLazySingleton& operator=(const ThreadSafeLazySingleton&) = delete;
};

ThreadSafeLazySingleton* ThreadSafeLazySingleton::instance = nullptr;
std::mutex ThreadSafeLazySingleton::mutex;

int main() {
    ThreadSafeLazySingleton* singleton = ThreadSafeLazySingleton::getInstance();
    std::cout << "Singleton address: " << singleton << std::endl;
    return 0;
}


// 饿汉式单例
#include <iostream>

class EagerSingleton {
private:
    static EagerSingleton instance;  // 在程序开始时即初始化实例

    EagerSingleton() {}  // 私有构造函数

public:
    static EagerSingleton& getInstance() {
        return instance;
    }

    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;
};

// 初始化静态成员变量
EagerSingleton EagerSingleton::instance;

int main() {
    EagerSingleton& singleton = EagerSingleton::getInstance();
    std::cout << "Singleton address: " << &singleton << std::endl;
    return 0;
}


/*在饿汉式单例模式中，实例在程序启动时立即被创建，因此不存在线程安全问题。但是，这意味着即使这个实例从未被使用，它也会占用资源。
注意：以上懒汉式和饿汉式的实现都没有考虑到对象析构的顺序问题，可能会在程序结束时遇到静态析构顺序问题。为了处理这个问题，
你可以将实例存储在本地静态变量中（在函数内部），这样可以利用局部静态变量初始化顺序的特性来保证正确的构造和析构。*/
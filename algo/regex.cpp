#include <iostream>
#include <string>
#include <regex>

bool isValidIPAddress(const std::string& ip) {
    // 定义一个IPv4地址的正则表达式模式
    std::regex ip_pattern(R"((\b25[0-5]\b|\b2[0-4][0-9]\b|\b[01]?[0-9][0-9]?\b)\.(\b25[0-5]\b|\b2[0-4][0-9]\b|\b[01]?[0-9][0-9]?\b)\.(\b25[0-5]\b|\b2[0-4][0-9]\b|\b[01]?[0-9][0-9]?\b)\.(\b25[0-5]\b|\b2[0-4][0-9]\b|\b[01]?[0-9][0-9]?\b))");
    
    // 使用正则表达式来匹配传入的IP地址字符串
    return std::regex_match(ip, ip_pattern);
}

int main() {
    // 测试isValidIPAddress函数
    std::string ip = "1.16.8.1";
    if (isValidIPAddress(ip)) {
        std::cout << ip << " is a valid IPv4 address." << std::endl;
    } else {
        std::cout << ip << " is not a valid IPv4 address." << std::endl;
    }

    return 0;
}

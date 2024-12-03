#include<iostream>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

inline bool is_digit(const char c)
{
    return c >= '0' && c <= '9';
}


int main()
{
    std::string line;
    uint64_t sum = 0;
    uint64_t sum_2 = 0;
    while (std::getline(std::cin, line))
    {
        char first_digit = -1;
        char last_digit = -1;
        for (auto it = line.begin(); it != line.end(); ++it) {
            const char c = *it;
            if (is_digit(c)){
                first_digit = c - '0';
                break;
            }
        }
        for (auto it = line.rbegin(); it != line.rend(); ++it) {
            const char c = *it;
            if (is_digit(c)){
                last_digit = c - '0';
                break;
            }
        }
        if (first_digit != -1 && last_digit != -1) {
            sum += first_digit * 10 + last_digit;
        }
        first_digit = -1;
        last_digit = -1;
    }
    std::cout << sum << std::endl;
    std::cout << sum_2 << std::endl;


    return 0;
}

#include<iostream>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <array>

inline bool is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

std::array<std::string, 9> numbers_str = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

char first_number(const std::string &str){
    char first_digit = -1;
    for (auto it = str.begin(); it != str.end(); ++it) {
        const char c = *it;
        if (is_digit(c)){
            return c - '0';
        } else {
            for (size_t i = 0; i < numbers_str.size(); i++){
                for(size_t j = 0; j < numbers_str[i].length(); j++){
                    if ((it + j) != str.end() && *(it + j) == numbers_str[i][j]) {
                        first_digit = i + 1;
                    } else {
                        first_digit = -1;
                        break;
                    }
                }
                if (first_digit != -1){
                    return first_digit;
                }   
            }
        }
    }
    return first_digit;
}

char last_number(const std::string &str){
    char last_digit = -1;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        const char c = *it;
        if (is_digit(c)){
            last_digit = c - '0';
            break;
        } else {
            for (size_t i = 0; i < numbers_str.size(); i++){
                for(size_t j = numbers_str[i].length(); j > 0; j--){
                    if ((it + (numbers_str[i].length() - j)) != str.rend() && *(it + (numbers_str[i].length() - j)) == numbers_str[i][j - 1]) {
                        last_digit = i + 1;
                    } else {
                        last_digit = -1;
                        break;
                    }
                }
                if (last_digit != -1){
                    return last_digit;
                } 
            }
        }
    }
    return last_digit;
}

int main()
{
    std::string line;
    uint64_t sum = 0;
    while (std::getline(std::cin, line))
    {
        char first_digit = first_number(line);
        char last_digit = last_number(line);

        if (first_digit != -1 && last_digit != -1) {
            sum += first_digit * 10 + last_digit;
        }
        first_digit = -1;
        last_digit = -1;
    }
    std::cout << sum << std::endl;


    return 0;
}

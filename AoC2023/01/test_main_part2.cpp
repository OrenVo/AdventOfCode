#include <gtest/gtest.h>

// Include the header file that contains the last_number function

inline bool is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

std::array<std::string, 9> numbers_str = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

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
                    if ((it - j) != str.rend() && *(it - j) == numbers_str[i][j]) {
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

// Test case for last_number function
TEST(LastNumberTest, ReturnsCorrectLastNumber) {
    // Test input string with a single digit
    std::string str1 = "abc123";
    EXPECT_EQ(last_number(str1), 3);

    // Test input string with multiple digits
    std::string str2 = "abc123def456";
    EXPECT_EQ(last_number(str2), 6);

    // Test input string with no digits
    std::string str3 = "abcdef";
    EXPECT_EQ(last_number(str3), -1);

    // Test input string with digits at the beginning
    std::string str4 = "123abc";
    EXPECT_EQ(last_number(str4), 3);

    // Test input string with digits at the end
    std::string str5 = "abc456";
    EXPECT_EQ(last_number(str5), 6);
    std::string str6 = "abc456one";
    EXPECT_EQ(last_number(str6), 1);
    std::string str7 = "abc456onesix";
    EXPECT_EQ(last_number(str7), 6);
    std::string str8 = "abc456nineone";
    EXPECT_EQ(last_number(str8), 1);
        std::string str9 = "oneabc";
    EXPECT_EQ(first_number(str9), 1);
    std::string str10 = "twoabc";
    EXPECT_EQ(first_number(str10), 2);
    std::string str11 = "threeabc";
    EXPECT_EQ(first_number(str11), 3);
    std::string str12 = "fourabc";
    EXPECT_EQ(first_number(str12), 4);
    std::string str13 = "fiveabc";
    EXPECT_EQ(first_number(str13), 5);
    std::string str14 = "sixabc";
    EXPECT_EQ(first_number(str14), 6);
    std::string str15 = "sevenabc";
    EXPECT_EQ(first_number(str15), 7);
    std::string str16 = "eightabc";
    EXPECT_EQ(first_number(str16), 8);
    std::string str17 = "nineabc";
    EXPECT_EQ(first_number(str17), 9);
}

// Test case for last_number function
TEST(FirstNumberTest, ReturnsCorrectFirstNumber) {
    // Test input string with a single digit
    std::string str1 = "abc123";
    EXPECT_EQ(first_number(str1), 1);

    // Test input string with multiple digits
    std::string str2 = "abc123def456";
    EXPECT_EQ(first_number(str2), 1);

    // Test input string with no digits
    std::string str3 = "abcdef";
    EXPECT_EQ(first_number(str3), -1);

    // Test input string with digits at the beginning
    std::string str4 = "123abc";
    EXPECT_EQ(first_number(str4), 1);

    // Test input string with digits at the end
    std::string str5 = "abc456";
    EXPECT_EQ(first_number(str5), 4);
    std::string str6 = "abc456one";
    EXPECT_EQ(first_number(str6), 4);
    std::string str7 = "absixc456one";
    EXPECT_EQ(first_number(str7), 6);
    std::string str8 = "aonebc456nine";
    EXPECT_EQ(first_number(str8), 1);

    // Additional tests for strings starting with numbers from one to nine
    std::string str9 = "oneabc";
    EXPECT_EQ(first_number(str9), 1);
    std::string str10 = "twoabc";
    EXPECT_EQ(first_number(str10), 2);
    std::string str11 = "threeabc";
    EXPECT_EQ(first_number(str11), 3);
    std::string str12 = "fourabc";
    EXPECT_EQ(first_number(str12), 4);
    std::string str13 = "fiveabc";
    EXPECT_EQ(first_number(str13), 5);
    std::string str14 = "sixabc";
    EXPECT_EQ(first_number(str14), 6);
    std::string str15 = "sevenabc";
    EXPECT_EQ(first_number(str15), 7);
    std::string str16 = "eightabc";
    EXPECT_EQ(first_number(str16), 8);
    std::string str17 = "nineabc";
    EXPECT_EQ(first_number(str17), 9);
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
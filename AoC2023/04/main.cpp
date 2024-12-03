#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cassert>
#include <array>

std::vector<std::string> split(std::string &str, char del = ' '){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, del)){
        result.push_back(token);
    }
    return result;
}

std::vector<int> split_int(std::string &str, char del = ' '){
    std::vector<int> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, del)){
        if (token == " " || token == "")
            continue;
        result.push_back(std::stoi(token));
    }
    return result;
}

int main(){
    uint64_t sum = 0;
    uint64_t sum_cards = 0;
    std::string line;
    std::vector<int> ids = {};
    ids.reserve(1024*1024);
    while (std::getline(std::cin, line)){    
        sum_cards++;
        const auto id_it = std::find(line.begin(), line.end(), ':');
        std::string id_str(std::find(line.begin(), id_it, ' '), id_it);
        int id = std::stoi(id_str);
        const auto win_it = std::find(line.begin(), line.end(), '|');
        std::string win_numbers_str = std::string(id_it + 1, win_it);
        std::string numbers_str = std::string(win_it + 1, line.end());
        //std::cout << win_numbers_str << std::endl << numbers_str << std::endl;
        std::vector<int> win_numbers = split_int(win_numbers_str);
        std::vector<int> numbers = split_int(numbers_str);
        
        int res = 0;
        int num_of_wins = 0;
        for(const int num : numbers){
            const auto it = std::find(win_numbers.begin(), win_numbers.end(), num);
            if (it != win_numbers.end()){
                num_of_wins++;
                if(res)
                    res = res << 1;
                else
                    res = 1;
            }
        }
        sum += res;
        for (int i = 1; i <= num_of_wins; i++){
            sum_cards++;
            ids.push_back(id + i);
        }
        int n_of_this_card = 0;
        
        #pragma omp for simd
        for(size_t i = 0; i < ids.size(); i++){
            n_of_this_card += (ids[i] == id);
        }
        for (int i = 0; i < n_of_this_card; i++){
            for (int i = 1; i <= num_of_wins; i++){
                sum_cards++;
                ids.push_back(id + i);
            }
        }
        //sum_cards += n_of_this_card * num_of_wins;      
    }
    //std::cout << sum << std::endl; // Answer part 1
    std::cout << sum_cards << std::endl;
    
    return 0;
}
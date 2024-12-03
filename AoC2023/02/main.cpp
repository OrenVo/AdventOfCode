#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <iomanip>

// 12 red cubes, 
// 13 green cubes
// 14 blue cubes

std::vector<std::string> split(std::string &str, char del = ' '){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, del)){
        result.push_back(token);
    }
    return result;
}

int main(){
    const char max_red = 12;
    const char max_green = 13;
    const char max_blue = 14;
    uint64_t sum = 0;
    int sum_of_power = 0;
    std::string line;
    while (std::getline(std::cin, line)){
        
        const auto id_it = std::find(line.begin(), line.end(), ':');
        std::string id_str(std::find(line.begin(), id_it, ' '), id_it);
        int id = std::stoi(id_str);
        sum += id;
        std::string sets_str = std::string(id_it + 1, line.end());
        std::vector<std::string> sets = split(sets_str, ';');
        uint64_t min_red = 1;
        uint64_t min_green = 1;
        uint64_t min_blue = 1;
        bool subtract_once = true;
        for (auto& s : sets){
            std::vector<std::string> set = split(s, ',');
            uint64_t red = 0;
            uint64_t green = 0;
            uint64_t blue = 0;

            for (auto &color : set){
                std::vector<std::string> splited = split(color, ' ');
                int color_count = std::stoi(splited[1]);
                if (splited[2] == "red") {
                    red += color_count;
                } else if (splited[2] == "blue"){
                    blue += color_count;
                } else if (splited[2] == "green"){
                    green += color_count;
                }    
            }
            min_red = std::max(min_red, red);
            min_green = std::max(min_green, green);
            min_blue = std::max(min_blue, blue);

            if ((max_red < red || max_green < green || max_blue < blue) && subtract_once) {
                subtract_once = false;
                sum -= id;
            }
                    
            red = 0; green = 0; blue = 0;
        }   
        sum_of_power += (min_red * min_green * min_blue);
        std::cout << line << std::endl;
        std::cout << "Game " << id << ": Red: " << min_red << " Green: " << min_green << " Blue: " << min_blue << " cum_sum: " << sum_of_power << std::endl;
    }
    std::cout << "Part 1: " << sum << std::endl;
    std::cout << "Part 2: " << sum_of_power << std::endl;
    return 0;
}
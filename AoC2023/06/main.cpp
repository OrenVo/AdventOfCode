#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cassert>
#include <array>
#include <queue>
#include <stack>


std::vector<size_t> split_int(std::string &str, char del = ' '){
    std::vector<size_t> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, del)){
        if (token == " " || token == "")
            continue;
        result.push_back(std::stoll(token));
    }
    return result;
}

struct Race {
    int64_t time;
    int64_t distance;
    Race(int64_t time, int64_t distance): time(time), distance(distance){}
};

int64_t compute_race(const Race &r){
    int64_t result = 0;
    for (int64_t hold = 1; hold < r.time; hold++) {
        int64_t distance = hold * (r.time - hold);
        if (distance > r.distance) {
            {
                #pragma omp critical
                ;
            }
            result++;
        }
    }
    return result;
}

int main(){
    std::string line;
    std::vector<size_t> times;
    std::vector<size_t> distances;
    std::vector<Race> races;
    int64_t result = 1;
    int64_t time;
    int64_t distance;
    if (std::getline(std::cin, line)) {
        const auto num_it = std::find(line.begin(), line.end(), ':');
        std::string num_str(num_it + 1, line.end());
        times = split_int(num_str);
        while(true){
            auto it = std::find(num_str.begin(), num_str.end(), ' ');
            if (it == num_str.end()){
                break;
            }else{
                num_str.erase(it);
            }
        }
        time = std::stoll(num_str);
    } else {
        std::cerr << "Error: no input" << std::endl;
        return 1;
    }
    if (std::getline(std::cin, line)) {
        const auto num_it = std::find(line.begin(), line.end(), ':');
        std::string num_str(num_it + 1, line.end());
        distances = split_int(num_str);
        while(true){
            auto it = std::find(num_str.begin(), num_str.end(), ' ');
            if (it == num_str.end()){
                break;
            }else{
                num_str.erase(it);
            }
        }
        distance = std::stoll(num_str);
    } else {
        std::cerr << "Error: no input" << std::endl;
        return 1;
    }
    Race part2_race = {time, distance};
    assert(times.size() == distances.size());
    for (size_t i = 0; i < times.size(); i++) {
        races.emplace_back(times[i], distances[i]);
    }
    
    for (size_t i = 0; i < races.size(); i++) {
        int64_t res = compute_race(races[i]);
        result = result * res;
    }
    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Part 2: " << compute_race(part2_race) << std::endl;
    return 0;
}
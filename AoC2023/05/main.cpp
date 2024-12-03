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

class Range {
public:
    size_t start = 0;
    size_t size = 0;
    size_t end = 0;
    Range(size_t start, size_t size): start(start), size(size){
        end = start + size - 1;
    }
    size_t operator[](const size_t index) {
        assert(index <= size);
        return start + index - 1;
    }
    inline bool operator==(const size_t &num) const {
        return num >= start && num <= end;
    }
    size_t get_index(size_t num){
        if (num >= start && num <= end){
            return num - start + 1;
        }
        return SIZE_MAX;
    }

};

class Map {
public: 
    std::string name = "";
    std::vector<std::pair<Range, Range>> ranges = {};
    void add_range(Range dest, Range src){
        ranges.emplace_back(dest, src);
    }
    void add_range(size_t dest_start, size_t src_start, size_t size){
        ranges.emplace_back(Range{dest_start, size},Range{src_start, size});
    }
};

struct queue_item {
    size_t value;
    std::vector<Map> maps;
};

void fill_locations(std::vector<size_t> &locations, const std::vector<size_t> &seeds, const std::vector<Map> &maps){
    std::queue<queue_item> q;

    for (const auto seed : seeds){
        q.push(queue_item{seed, maps});
    }

    while(not q.empty()){
        queue_item item = q.front();
        q.pop();
        Map map = item.maps.front();
        if (item.maps.size() == 1){
            bool found = false;
            auto min = std::min_element(locations.begin(), locations.end());
            size_t min_loc = UINT64_MAX;
            if (min != locations.end()){
                min_loc = *min;
            }
            
            for (size_t i = 0; i < map.ranges.size(); i++) {    
                if (map.ranges[i].second == item.value){
                    size_t idx = map.ranges[i].second.get_index(item.value);
                    size_t loc = map.ranges[i].first[idx];
                    if (loc > min_loc)
                        continue;
                    {
                        #pragma omp critical
                        locations.push_back(loc);
                        std::cerr << "New min: " << loc << std::endl;
                    }
                    found = true;
                }
            }
            if (not found) {
                if (item.value < min_loc){
                    #pragma omp critical
                    locations.push_back(item.value);
                }
            }
        } else {
            bool pushed = false;
            for (size_t i = 0; i < map.ranges.size(); i++) {
                if (map.ranges[i].second == item.value){
                    size_t idx = map.ranges[i].second.get_index(item.value);
                    size_t loc = map.ranges[i].first[idx];
                    q.push(queue_item{loc, std::vector<Map>(item.maps.begin() + 1, item.maps.end())});
                    pushed = true;
                }
            }
            if(not pushed){
                q.push(queue_item{item.value, std::vector<Map>(item.maps.begin() + 1, item.maps.end())});
            }
        }
    }
}



int main(){
    std::string line;
    std::vector<Map> maps;
    std::vector<size_t> seeds;
    std::vector<size_t> locations;
    if (std::getline(std::cin, line)) {
        const auto num_it = std::find(line.begin(), line.end(), ':');
        std::string num_str(num_it + 1, line.end());
        seeds = split_int(num_str);
    }
    // Debug
    std::cerr << "Seeds: ";
    for (const auto seed : seeds){
        std::cerr << seed << " ";
    }
    std::cerr << std::endl;

    while (std::getline(std::cin, line)){   // parse maps
        if  (line == "")
            continue;
        const auto name_it = std::find(line.begin(), line.end(), ':');
        if (name_it != line.end()) {
            maps.push_back(Map());
            maps.back().name = std::string(line.begin(), name_it);
            if(!std::getline(std::cin, line)){
                std::cerr << "Unexpected end of input" << std::endl;
                break;
            }
            while(line != ""){
                if (line == "")
                    break;
                std::vector<size_t> numbers = split_int(line);
                assert(numbers.size() == 3);
                maps.back().add_range(numbers[0], numbers[1], numbers[2]);
                std::getline(std::cin, line);
            }
            std::cerr << "Map: " << maps.back().name << ": " << std::endl;
            for (const auto &range : maps.back().ranges){
                std::cerr << "    " << range.first.start << " - " << range.first.end << " -> " << range.second.start << " - " << range.second.end << std::endl;
            }
        } 
    }

    fill_locations(locations, seeds, maps);
    std::cout << "Part 1: " << std::endl << "Locations: " << std::endl;
    //for (const size_t loc : locations){        
    //    std::cout << loc << std::endl;
    //}
    auto min = std::min_element(locations.begin(), locations.end());
    if (min != locations.end())
        std::cout << "Min location: " << *min << std::endl;
    else
        std::cout << "No min location" << std::endl;
    
    (void) locations;

    std::vector<size_t> locations_part2 = {};
    std::vector<size_t> seeds_part2 = {};
    for (size_t i = 0; i < seeds.size(); i++){
        size_t seed_start = seeds[i];
        size_t seed_end = seeds[++i];
        //It still takes 30 mins to get result... :/ 
        #pragma omp parallel for num_threads(12) schedule(dynamic)
        for (size_t i = seed_start; i < seed_start + seed_end; i++) {
            fill_locations(locations_part2, {i}, maps);
        }
    }
    try{
        std::cout << "Part 2: " << std::endl << "Locations: " << std::endl;
        for (const size_t loc : locations_part2){        
            std::cout << loc << std::endl;
        }
        auto min_part2 = std::min_element(locations_part2.begin(), locations_part2.end());
        if (min_part2 != locations_part2.end())
            std::cout << "Min location: " << *min_part2 << std::endl;
        else
            std::cout << "No min location" << std::endl;
    } catch (std::exception const& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
} 
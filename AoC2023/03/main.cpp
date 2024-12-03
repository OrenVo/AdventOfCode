#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cassert>
#include <array>

struct token {
    enum token_type {none, number, symbol} typedef token_type_t;
    union data {
        size_t number;
        char symbol;
    } typedef data_t;
    
    token_type_t type = none;
    data_t data = {};
    size_t index_start;
    size_t index_end;
    size_t line_number;
    
    
} typedef token_t;

struct index {
    size_t line_index;
    size_t line_number;
} typedef index_t;

struct number {
    size_t data;
    size_t line_number;
    size_t index_start;
    size_t index_end;
    std::vector<index_t> perimeter_indexes = {};

    number(size_t data, size_t line_number, size_t index_start, size_t index_end, const std::vector<index_t> &perimeter_indexes) : data(data), 
        line_number(line_number), index_start(index_start), index_end(index_end), perimeter_indexes(perimeter_indexes) {
        
    }
} typedef number_t;



std::vector<index_t> compute_perimeter(size_t index_start, size_t index_end, size_t line_number){
    std::vector<index_t> perimeter_indexes = {};
    if (line_number > 0) {
        if (index_start > 0) {
            perimeter_indexes.emplace_back(index_start - 1, line_number - 1);
        }
        perimeter_indexes.emplace_back(index_end, line_number - 1);
    }
    perimeter_indexes.emplace_back(index_end, line_number + 1);
    perimeter_indexes.emplace_back(index_end, line_number);
    if (index_start > 0) {
        perimeter_indexes.emplace_back(index_start - 1, line_number);
        perimeter_indexes.emplace_back(index_start - 1, line_number + 1);
    }
    for (size_t i = index_start; i < index_end+1; i++){
        if (line_number > 0) {
            perimeter_indexes.emplace_back(i, line_number - 1);
        }
        perimeter_indexes.emplace_back(i, line_number + 1);
    }
    return perimeter_indexes;
}

token_t parse_input(const std::vector<std::string> &input, size_t line_number, size_t line_idx){
    token_t token = {};
    size_t line_idx_copy = line_idx;
    token.type = token_t::token_type_t::none;
    for (size_t i = line_number; i < input.size(); i++) {
        for (size_t j = line_idx_copy; j < input[i].length(); j++) {
            if (input[i][j] == '.' || input[i][j] == '\n') {
                continue;
            } else if (isdigit(input[i][j])){
                size_t end = j;
                for(;end < input[i].length() && isdigit(input[i][end]);)
                    end++;
                token.type = token::token_type_t::number;
                token.data.number = std::stoull(std::string(input[i].c_str() + j, end - j));
                token.index_start = j;
                token.index_end = end;
                token.line_number = i;
                return token;
            } else {
                token.type = token::token_type_t::symbol;
                token.data.symbol = input[i][j];
                token.index_start = j;
                token.index_end = j+1;
                token.line_number = i;
                return token;
            }
        }
        line_idx_copy = 0;
    }
    return token;
}


int main(){
    
    std::vector<index_t> symbol_idx = {};
    std::vector<number_t> number = {};
    std::string line;
    std::vector<std::string> input = {};
    std::vector<index_t> gears = {};
    while(std::getline(std::cin, line)){
        input.push_back(line);
    }
    token_t t = parse_input(input, 0, 0);
    int i = 0;
    while(t.type != token_t::token_type_t::none){
        if (t.type == token_t::token_type_t::number) {
            number.emplace_back(t.data.number, t.line_number, t.index_start, t.index_end, compute_perimeter(t.index_start, t.index_end, t.line_number));
        } else if (t.type == token_t::token_type_t::symbol) {
            if (t.data.symbol == '*'){
                gears.emplace_back(t.index_start, t.line_number);
            }
            
            symbol_idx.emplace_back(t.index_start, t.line_number);

        }
        t = parse_input(input, t.line_number, t.index_end);
        i++;
    }
    std::cout << std::endl;
    size_t sum = 0;
    for(const index_t &sym_idx :symbol_idx){
        std::cout << sym_idx.line_index << " " << sym_idx.line_number << std::endl;
    }
    for (const number_t &num : number){
        if (num.data == 631){
            std::cout << "Num 631: " << num.index_start << " " << num.index_end << " " << num.line_number << " " << std::endl;
            for (const index_t idx : num.perimeter_indexes){
                std::cout << idx.line_index << " " << idx.line_number << std::endl;
            }
        }
        
        for (const index_t idx : num.perimeter_indexes){
            bool found = false;
            for(const index_t &sym_idx :symbol_idx){
                if (sym_idx.line_index == idx.line_index && sym_idx.line_number == idx.line_number) {   
                    std::cout << num.data << " "; 
                    found = true;
                    sum += num.data;
                    break;
                }   
            }
            if (found) break;
        }
    }
    uint64_t sum2 = 0;
    for(const index_t gear_idx : gears){
        bool is_gear = false;
        int count = 0;
        std::array<size_t,2> numbers = {0,0};
        for (const number_t &num : number){
            for (const index_t idx : num.perimeter_indexes){
                if (gear_idx.line_index == idx.line_index && gear_idx.line_number == idx.line_number) {
                    if (numbers[0] == 0) {
                        numbers[0] = num.data;
                    } else {
                        numbers[1] = num.data;
                    }
                    count++;
                    if (count == 2) {
                        is_gear = true;
                    }
                    break;
                }
                if (count > 2){
                    is_gear = false;
                    break;
                }
            }
        }
        if (is_gear){
            sum2 += numbers[0] * numbers[1];
        }
        
    }

    std::cout << std::endl << "Sum: " << sum << std::endl;
    std::cout << std::endl << "Sum_part2: " << sum2 << std::endl;

    return 0;
}

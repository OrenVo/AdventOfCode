#include <cmath>
#include <stack>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <vector>
#include <cstdint>


struct CalibrationEquation {
    uint64_t result;
    std::vector<uint64_t> values;
    const size_t number_of_operators = 0;
    CalibrationEquation(uint64_t result, std::vector<uint64_t> values): result(result), values(values), number_of_operators(values.size() - 1) {}
};

std::vector<CalibrationEquation> parseInput(std::string filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return {};
    }
    std::vector<CalibrationEquation> result;
    std::string line;
    while (getline(inputFile, line)) {
        uint64_t firstNumber;
        std::vector<uint64_t> numbers;
        std::stringstream ss(line);

        // Read the first number and the colon
        ss >> firstNumber;
        char colon;
        ss >> colon;

        // Read the rest of the numbers
        size_t length = 0;
        int num;
        while (ss >> num) {
            length++;
            numbers.push_back(num);
        }
        result.emplace_back(firstNumber, numbers);
    }
    inputFile.close();
    return result;
}

enum op {
    add,
    mul,
    concat
};

std::vector<std::vector<op>> generateOperators(size_t size){
    std::vector<std::vector<op>> result;
    size_t number_of_permutations = std::pow(std::uint64_t(2), size);
    result.reserve(number_of_permutations);
    for (size_t i = 0; i < number_of_permutations; i++){
        std::vector<op> permutation;
        permutation.reserve(size-1);
        for (size_t j = 0; j < size; j++){
            if(i & (1 << j)){ // if bit j-th is set to 1 push add op
                permutation.push_back(add);
            } else { // else push mul op
                permutation.push_back(mul);
            }
        }
        result.emplace_back(permutation);
    }
    return result;
}

std::pair<uint64_t, std::set<size_t>> part1(std::vector<CalibrationEquation> eqs){
    std::map<size_t, std::vector<std::vector<op>>> operations;
    uint64_t cumsum = 0;
    std::set<size_t> indices;
    for (size_t i = 0; i< eqs.size(); i++){
        CalibrationEquation &e = eqs[i];
        if (!operations.contains(e.number_of_operators)){
            operations[e.number_of_operators] = generateOperators(e.number_of_operators);
        }
        bool valid = false;
        for (auto &op : operations[e.number_of_operators]) {
            uint64_t value = e.values[0];
            for (size_t i = 0; i < op.size(); i++ ) {
                if (op[i] == add) {
                    value += e.values.at(i+1);
                } else {
                    value *= e.values.at(i+1);
                }
                if (value > e.result) break;
            }
            if (value == e.result) {
                valid = true;
                break;
            }
        }
        if (valid) {
            indices.insert(i);
            cumsum += e.result;
        }
    }
    return {cumsum, indices};
}

uint64_t concatOperator(uint64_t a, uint64_t b){
    uint64_t temp = b;
    int digits = 0;
    if (temp == 0) digits = 1;
    while (temp > 0) {
        temp /= 10;
        digits++;
    }
    return uint64_t(a * std::pow(10, digits) + b);
}

uint64_t tryWithConcatOperator(CalibrationEquation e){
    struct stackData {
        uint64_t cumulative_value = 0;
        std::vector<uint64_t>::iterator current_value;
    };
    std::stack<stackData> treeStack;
    treeStack.emplace(e.values[0], (++e.values.begin()));
    while (!treeStack.empty()) {
        stackData curr = treeStack.top();
        treeStack.pop();

        if (curr.current_value == e.values.end()){
            if (curr.cumulative_value == e.result) return e.result;
            else continue; // no more values in vector
        }

        // Try add
        treeStack.emplace((curr.cumulative_value + (*curr.current_value)), (curr.current_value + 1));
        // Try mul
        treeStack.emplace((curr.cumulative_value * (*curr.current_value)), (curr.current_value + 1));
        // Try concat
        treeStack.emplace(concatOperator(curr.cumulative_value, (*curr.current_value)), (curr.current_value + 1));
    }
    return 0;
}

uint64_t part2(std::vector<CalibrationEquation> eqs){
    uint64_t result = 0;
    #pragma omp parallel for num_threads(12) schedule(dynamic)
    
    for (CalibrationEquation &e : eqs){
        uint64_t res = tryWithConcatOperator(e);
        {
            #pragma omp critical
            result += res;
        }
    }
    return result;
}

int main() {
    using namespace std::chrono;
    auto start_p = high_resolution_clock::now();
    std::vector<CalibrationEquation> input = parseInput("input");
    auto stop_p = high_resolution_clock::now();
    auto duration_p = duration_cast<microseconds>(stop_p - start_p);
    auto start_p1 = high_resolution_clock::now();
    auto res1 = part1(input);
    auto stop_p1 = high_resolution_clock::now();
    auto duration_p1 = duration_cast<microseconds>(stop_p1 - start_p1);
    std::cout << "Part 1: " << res1.first << std::endl;
    auto start_p2 = high_resolution_clock::now();
    std::vector<CalibrationEquation> filtered;
    for (size_t i = 0; i < input.size(); i++) { // Copy only bad equations
        if (res1.second.contains(i)) continue;
        else filtered.push_back(input[i]);
    }
    uint64_t res2 = part2(filtered);
    auto stop_p2 = high_resolution_clock::now();
    auto duration_p2 = duration_cast<milliseconds>(stop_p2 - start_p2);
    std::cout << "Part 2: " << (res1.first + res2) << std::endl;

    std::cout << "Time taken by parsing: " << duration_p.count() << " μs" << std::endl;
    std::cout << "Time taken by part 1: " << duration_p1.count() << " μs" << std::endl;
    std::cout << "Time taken by part 2: " << duration_p2.count() << " ms" << std::endl;
    return 0;
}

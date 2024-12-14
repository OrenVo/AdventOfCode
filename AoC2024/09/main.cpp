#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>
enum BlockType {
  Free,
  File
};

struct Block {
  int size;
  BlockType type;
  int ID;

  Block(int size, BlockType type, int ID) : size(size), type(type), ID(ID) {}
  bool operator<(const Block& other) const {
    return size < other.size;
  }
};

std::vector<Block> createFS(std::vector<uint64_t> &nums){
    std::vector<Block> result;
    int file_id = 0;
    int free_id = 0;
    bool isFile = true;
    for (int n :nums){
        result.emplace_back(n,isFile ? File : Free,isFile ? file_id++ : free_id++);
        isFile = !isFile;
    }
    return result;
}

std::vector<Block> compactFS(const std::vector<Block> &FS) {
    std::vector<Block> result(FS);
    std::vector<Block> files;
    std::copy_if(result.rbegin(), result.rend(),std::back_inserter(files), [](const Block & b){
        return b.type == File;
    });
    for (const Block &b : files) {
        bool found = false;
        size_t space_idx = 0;
        assert(b.type != Free);
        for (; space_idx < result.size(); space_idx++) {
            if (result[space_idx].type == File && b.ID == result[space_idx].ID) {
                break;
            }
            if (result[space_idx].type == Free && result[space_idx].size >= b.size) {
                found = true;
                break;
            }
        }
        if (found) {
            assert(result[space_idx].type == Free);
            assert(result[space_idx].size >= b.size);
            result[space_idx].size -= b.size;
            result.insert(result.begin() + space_idx, {b.size, b.type, b.ID});
            for (size_t i = result.size() - 1; i > 0; i--){
                if (result[i].type == File && result[i].ID == b.ID) {
                    result[i].type = Free;
                    break;
                }
            }
        }
    }
    return result;
}

uint64_t checkSum(const std::vector<Block> &FS) {
    std::vector<uint64_t> mem;
    // std::cout << "Memory for sum: ";
    for (const Block &b : FS){
        for (int i = 0; i < b.size; i++) {
            // std::cout << " " << (b.type == Free ? "." : std::to_string(b.ID));
            mem.push_back(b.type == Free ? 0 : b.ID);
        }
    }
    // std::cout << std::endl;
    uint64_t result = 0;
    #pragma omp for simd
    for (size_t i = 0; i < mem.size(); i++) {
        result += i * mem[i];
    }
    return result;
}

int main() {
    std::vector<uint64_t> numbers;
    char ch;

    while (std::cin.get(ch)) {
        if (std::isdigit(ch)) {
            uint64_t digit = ch - '0';
            numbers.push_back(digit);
        }
    }
    std::vector<Block> FS = createFS(numbers);
    std::vector<Block> res = compactFS(FS);
    // std::cout << "Compacted memory: [";
    // for (auto b : res){
    //     if (b.type == File){
    //         std::cout << "File<" << b.ID << ", " << b.size << ">, ";
    //     } else {
    //         std::cout << "Free<" << b.ID << ", " << b.size << ">, ";
    //     }
    // }
    // std::cout << "]" << std::endl;
    uint64_t cs = checkSum(res);
    std::cout << "Part 2: " << cs << std::endl;
    return 0;
}


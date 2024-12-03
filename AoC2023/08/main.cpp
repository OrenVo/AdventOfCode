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
#include <numeric>


struct Node {
    std::string name = "";
    std::string leftName = "";
    Node *left = nullptr;
    std::string rightName = "";
    Node *right = nullptr;
};


int main() {
    std::string line;
    std::string directions = ""; 
    std::vector<Node> nodes;
    if (std::getline(std::cin, line)) {
        directions = line;
    }
    while (std::getline(std::cin, line)) {
        if (line == "")
            continue;
        auto it = line.find(" = ");
        if (it == std::string::npos)
            continue;
        
        std::string name = line.substr(0, it);
        std::string names = line.substr(it + 3, std::string::npos);
        std::string leftName = names.substr(names.find("(")+1, names.find(",")-1);
        std::string rightName = names.substr(names.find(" ")+1, names.find(")")-1);
        rightName.erase(rightName.find(")"), 1);
        nodes.emplace_back(name, leftName, nullptr, rightName, nullptr);
    }

    for (size_t i = 0; i < nodes.size(); i++){
        for (size_t j = 0; j < nodes.size(); j++){
            if (nodes[i].leftName == nodes[j].name){
                nodes[i].left = &nodes[j];
            }
            if (nodes[i].rightName == nodes[j].name){
                nodes[i].right = &nodes[j];
            }
        }
    }
    
    uint64_t count = 0;
    size_t idx = 0;
    Node *lastNode = &nodes[0];
    for (auto &node : nodes){
        if (node.name == "AAA"){
            lastNode = &node;
            break;
        }
    }
    for (;;){
        if (lastNode->name == "ZZZ"){
            break;
        }
        if (directions[idx] == 'L'){
            if (lastNode->left != nullptr){
                lastNode = lastNode->left;
            } else {
                std::cerr << "Error: " << lastNode->name << " has no left node" << std::endl;
                return 1;
            }
        }
        else if (directions[idx] == 'R'){
            if (lastNode->right != nullptr){
                lastNode = lastNode->right;
            } else {
                std::cerr << "Error: " << lastNode->name << " has no right node" << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "Error: " << directions[idx] << " is not a valid direction" << std::endl;
            return 1;
        }

        count++;
        idx++;
        if (idx >= directions.size())
            idx = 0;
    }
    std::cout << "Part 1: " << count << std::endl;

    std::vector<Node*> lastNodes;
    std::vector<size_t> counts;
    for (auto &node : nodes){
        if (node.name.back() == 'A'){
            lastNodes.push_back(&node);
        }
    }
    for (size_t i = 0; i < lastNodes.size();i++){
        size_t idx = 0;
        size_t count = 0;
        while(lastNodes[i]->name.back() != 'Z'){
            if (directions[idx] == 'L'){
                lastNodes[i] = lastNodes[i]->left;
            }
            else if (directions[idx] == 'R'){
                lastNodes[i] = lastNodes[i]->right;
            }
            idx++;
            count++;
            if (idx >= directions.size())
                idx = 0;
        }
        counts.push_back(count);
        std::cout << "Solved idx: " << i << " count: " << count << std::endl;
        
    }
    size_t count2 = std::lcm(counts[0], counts[1]);
    for (size_t i = 2; i < counts.size(); i++){
        count2 = std::lcm(count2, counts[i]);
    }
    std::cout << "Part 2: " << count2 << std::endl;

    return 0;
}
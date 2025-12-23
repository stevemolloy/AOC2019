#include <sstream>
#include <unordered_map>
#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

long find_chain_length(const string& node, const std::unordered_map<string, string>& links);
vector<string> find_chain(const string& node, const std::unordered_map<string, string> links);

int main(void) {
    string filename = "data/input.txt";
    // string filename = "data/test.txt";
    // string filename = "data/test2.txt";
    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Problem reading file");
        return 1;
    }
    vector<string> file_contents = result.value();

    std::unordered_map<string, string> links;
    for (const auto& line: file_contents) {
        std::stringstream ss(line);
        string key, val;
        std::getline(ss, val, ')');
        std::getline(ss, key, ')');

        links[key] = val;
    }

    long part1 = 0;
    for (const auto& node: links)
        part1 += find_chain_length(node.second, links);
    if (filename == "data/input.txt") assert(part1 == 145250);

    vector<string> you_2_com = find_chain("YOU", links);
    vector<string> san_2_com = find_chain("SAN", links);

    for (size_t i=0; i<you_2_com.size(); i++) {
        if (you_2_com.back() != san_2_com.back()) break;
        you_2_com.pop_back();
        san_2_com.pop_back();
    }

    long part2 = you_2_com.size() + san_2_com.size();
    if (filename == "data/input.txt") assert(part2 == 274);

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}

long find_chain_length(const string& node, const std::unordered_map<string, string>& links) {
    long distance = 1;
    string current = node;
    
    while (links.contains(current)) {
        current = links.at(current);
        distance++;
    }
    
    return distance;
}

vector<string> find_chain(const string& node, const std::unordered_map<string, string> links) {
    vector<string> chain;
    string current = node;
    while (links.contains(current)) {
        current = links.at(current);
        chain.push_back(current);
    }
    return chain;
}


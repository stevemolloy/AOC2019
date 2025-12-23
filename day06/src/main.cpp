#include <sstream>
#include <unordered_map>
#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

long find_chain_length(const string& node, const std::unordered_map<string, string>& links) {
    long distance = 1;
    string current = node;
    
    while (links.contains(current)) {
        current = links.at(current);
        distance++;
    }
    
    return distance;
}

int main(void) {
    string filename = "data/input.txt";
    // string filename = "data/test.txt";
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
    for (const auto& node: links) {
        part1 += find_chain_length(node.second, links);
    }
    assert(part1 == 145250);

    long part2 = 0;

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


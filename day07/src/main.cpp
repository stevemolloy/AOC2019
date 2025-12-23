#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
    string filename = "data/input.txt";
    // string filename = "data/test1.txt";
    // string filename = "data/test2.txt";
    // string filename = "data/test3.txt";

    // {
    //     vector<int> phases = {4,3,2,1,0};
    //     long prev_output = 0;
    //     for (int phase: phases) {
    //         Machine machine;
    //         machine.load_mem_from_file(filename);
    //         machine.add_input_val(prev_output);
    //         machine.add_input_val(phase);
    //         machine.run();
    //         prev_output = machine.output.back();
    //     }
    //     println("output = {}", prev_output);
    // }
    // return 0;

    vector<int> phases = {0, 1, 2, 3, 4};
    vector<vector<int>> phase_list;

    do {
        phase_list.push_back(phases);
    } while (std::ranges::next_permutation(phases).found);

    long best_output = 0;
    for (int i=0; const vector<int>& phases: phase_list) {
        long prev_output = 0;
        for (const int phase: phases) {
            Machine machine;
            machine.load_mem_from_file(filename);
            machine.add_input_val(prev_output);
            machine.add_input_val(phase);
            machine.run();
            if (machine.output.size() == 0) {
                println("{}: No output from this phase_list", i);
                break;
            }
            prev_output = machine.output.back();
        }
        println("{}: Final output: {}", ++i, prev_output);
        if (prev_output > best_output) best_output = prev_output; 
    }

    long part1 = best_output;
    long part2 = 0;

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


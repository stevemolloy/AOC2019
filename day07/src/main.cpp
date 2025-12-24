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
        if (prev_output > best_output) best_output = prev_output; 
    }

    long part1 = best_output;
    if (filename == "data/input.txt") assert(part1 == 20413);

    vector<Machine> amp_chain;
    for (size_t i=0; i<5; i++) {
        Machine machine;
        machine.load_mem_from_file(filename);
    }

    long part2 = 0;

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


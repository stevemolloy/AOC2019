#include <algorithm>
#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int drive_amp_chain(vector<Machine>& amp_chain, const vector<int>& phases, int input);
int drive_amp_chain_cont(vector<Machine>& amp_chain, const vector<int>& phases, int input);

int main(void) {
    string filename = "data/input.txt";
    // string filename = "data/test1.txt";
    // string filename = "data/test2.txt";
    // string filename = "data/test3.txt";
    // string filename = "data/test4.txt";

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
            assert(machine.input.size() == 0);
            prev_output = machine.output.back();
        }
        if (prev_output > best_output) best_output = prev_output; 
    }

    long part1 = best_output;
    if (filename == "data/input.txt") assert(part1 == 20413);

    phase_list.clear();
    phases = {5, 6, 7, 8, 9};
    do {
        phase_list.push_back(phases);
    } while (std::ranges::next_permutation(phases).found);

    filename = "data/test4.txt";
    long part2 = 0;
    for (const vector<int>& phases: phase_list) {
        vector<Machine> amp_chain;
        for (size_t i=0; i<5; i++)
            amp_chain.emplace_back(filename);
        int new_input = drive_amp_chain_cont(amp_chain, phases, 0);
        if (new_input > part2) part2 = new_input;
    }
    println("Final value of 'part2' = {}", part2);

    filename = "data/test5.txt";
    part2 = 0;
    for (const vector<int>& phases: phase_list) {
        vector<Machine> amp_chain;
        for (size_t i=0; i<5; i++)
            amp_chain.emplace_back(filename);
        int new_input = drive_amp_chain_cont(amp_chain, phases, 0);
        if (new_input > part2) part2 = new_input;
    }
    println("Final value of 'part2' = {}", part2);

    filename = "data/input.txt";
    part2 = 0;
    for (const vector<int>& phases: phase_list) {
        vector<Machine> amp_chain;
        for (size_t i=0; i<5; i++)
            amp_chain.emplace_back(filename);
        int new_input = drive_amp_chain_cont(amp_chain, phases, 0);
        if (new_input > part2) part2 = new_input;
    }
    println("Final value of 'part2' = {}", part2);

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}

int drive_amp_chain_cont(vector<Machine>& amp_chain, const vector<int>& phases, int input) {
    input = drive_amp_chain(amp_chain, phases, input);
    for (;;) {
        int new_input = drive_amp_chain(amp_chain, {}, input);
        if (new_input == input) break;
        input = new_input;
    }
    return input;
}

int drive_amp_chain(vector<Machine>& amp_chain, const vector<int>& phases, int input) {
    for (int i=0; Machine& amp: amp_chain) {
        amp.add_input_val(input);
        if (phases.size() > 0)
            amp.add_input_val(phases.at(i));
        amp.run();
        if (amp.output.size() == 0) {
            break;
        }
        input = amp.output.front();
        amp.output.pop_front();
        i += 1;
    }
    return input;
}


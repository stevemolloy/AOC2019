#include <algorithm>
#include <print>
#include <string>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
    int test_count=0, pass_count=0;
    println("------------------------------");
    println("            TESTS");
    println("------------------------------");
    test_count += 1;
    {
        string filename = "../day02/data/input.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.memory[1] = 12;
        machine.memory[2] = 2;
        if (machine.run() && machine.memory[0] == 5866714) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test1.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test1.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test2.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test2.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test3.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test3.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test4.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test4.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test5.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(1);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test5.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test6.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(1);
        if (machine.run() && machine.output.back() == 1) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test6.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        if (machine.run() && machine.output.back() == 0) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test7.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        if (machine.run() && machine.output.back() == 999) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test7.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        if (machine.run() && machine.output.back() == 1000) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "data/machine_test7.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.add_input_val(9);
        if (machine.run() && machine.output.back() == 1001) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        string filename = "../day02/data/input.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.memory[1] = 12;
        machine.memory[2] = 2;
        if (machine.run() && machine.memory[0] == 5866714) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        vector<vector<int>> phase_list;
        vector<int> phases = {5, 6, 7, 8, 9};
        do {
            phase_list.push_back(phases);
        } while (std::ranges::next_permutation(phases).found);

        string filename = "../day07/data/test4.txt";
        long result = 0;
        for (const vector<int>& phases: phase_list) {
            vector<Machine> amp_chain;
            for (size_t i=0; i<5; i++)
                amp_chain.emplace_back(filename);
            int new_input = drive_amp_chain_cont(amp_chain, phases, 0);
            if (new_input > result) result = new_input;
        }
        if (result == 139629729) pass_count += 1;
        else println("Test {}: Failed", test_count);
    }

    test_count += 1;
    {
        vector<vector<int>> phase_list;
        vector<int> phases = {5, 6, 7, 8, 9};
        do {
            phase_list.push_back(phases);
        } while (std::ranges::next_permutation(phases).found);

        string filename = "../day07/data/test5.txt";
        long result = 0;
        for (const vector<int>& phases: phase_list) {
            vector<Machine> amp_chain;
            for (size_t i=0; i<5; i++)
                amp_chain.emplace_back(filename);
            int new_input = drive_amp_chain_cont(amp_chain, phases, 0);
            if (new_input > result) result = new_input;
        }
        if (result == 18216) pass_count += 1;
        else println("Test {}: Failed", test_count);
        
    }

    println("Tests passed: {} / {}", test_count, pass_count);

    return 0;
}

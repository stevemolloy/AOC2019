#include <cassert>
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
        else println("Test 17: Failed");
    }

    println("Tests passed: {} / {}", test_count, pass_count);

    return 0;
}

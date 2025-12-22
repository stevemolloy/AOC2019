#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
    {
        println("------------------------------");
        println("            TESTS");
        println("------------------------------");
        string filename = "../day02/data/input.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.memory[1] = 12;
        machine.memory[2] = 2;
        assert(machine.run());
        assert(machine.memory[0] == 5866714);
        println("Test 1: Passed");
        println("------------------------------");

        filename = "data/test1.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 2: Passed");
        println("------------------------------");

        filename = "data/test1.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 3: Passed");
        println("------------------------------");

        filename = "data/test2.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 4: Passed");
        println("------------------------------");

        filename = "data/test2.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 5: Passed");
        println("------------------------------");

        filename = "data/test3.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 6: Passed");
        println("------------------------------");

        filename = "data/test3.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 7: Passed");
        println("------------------------------");

        filename = "data/test4.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 8: Passed");
        println("------------------------------");

        filename = "data/test4.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(7);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 9: Passed");
        println("------------------------------");

        filename = "data/test5.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(1);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 10: Passed");
        println("------------------------------");

        filename = "data/test5.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 11: Passed");
        println("------------------------------");

        filename = "data/test6.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(1);
        assert(machine.run());
        assert(machine.output.back() == 1);
        println("Test 12: Passed");
        println("------------------------------");

        filename = "data/test6.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        assert(machine.run());
        assert(machine.output.back() == 0);
        println("Test 13: Passed");
        println("------------------------------");

        filename = "data/test7.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(0);
        assert(machine.run());
        assert(machine.output.back() == 999);
        println("Test 14: Passed");
        println("------------------------------");

        filename = "data/test7.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(8);
        assert(machine.run());
        assert(machine.output.back() == 1000);
        println("Test 15: Passed");
        println("------------------------------");

        filename = "data/test7.txt";
        machine.load_mem_from_file(filename);
        machine.add_input_val(9);
        assert(machine.run());
        assert(machine.output.back() == 1001);
        println("Test 16: Passed");
        println("------------------------------");
    }

    string filename = "data/input.txt";
    Machine machine;
    machine.load_mem_from_file(filename);
    machine.add_input_val(1);
    assert(machine.run());
    long part1 = machine.output.back();

    Machine machine_part2;
    machine_part2.load_mem_from_file(filename);
    machine_part2.add_input_val(5);
    assert(machine_part2.run());
    long part2 = machine_part2.output.back();

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
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


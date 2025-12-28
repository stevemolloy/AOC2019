#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
    string filename = "data/input.txt";

    long part1;

    {
        Machine machine(filename);
        if (filename == "data/input.txt") machine.add_input_val(1);
        machine.run();
        part1 = machine.output[0];
        if (filename == "data/input.txt") assert(part1 == 3429606717);
    }

    long part2;
    {
        Machine machine(filename);
        if (filename == "data/input.txt") machine.add_input_val(2);
        machine.run();
        part2 = machine.output[0];
        if (filename == "data/input.txt") assert(part2 == 33679);
    }

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


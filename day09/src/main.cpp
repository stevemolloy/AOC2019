#include <cassert>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

int main(void) {
    string filename = "data/input.txt";

    Machine machine(filename);
    if (filename == "data/input.txt") machine.add_input_val(1);
    machine.run();

    long part1 = machine.output[0];
    if (filename == "data/input.txt") assert(part1 == 3429606717);

    long part2 = 0;
    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


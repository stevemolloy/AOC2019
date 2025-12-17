#include <cassert>
#include <charconv>
#include <expected>
#include <sstream>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

void interpret_instructions(vector<long>& instructions) {
    long i_count = instructions.size();

    for (long i=0; i<i_count; ) {
        long opcode = instructions[i];

        if (opcode == 1) {
            long param1 = instructions[i+1];
            long param2 = instructions[i+2];
            long result = instructions[i+3];
            instructions[result] = instructions[param1] + instructions[param2];
            i += 4;
        } else if (opcode == 2) {
            long param1 = instructions[i+1];
            long param2 = instructions[i+2];
            long result = instructions[i+3];
            instructions[result] = instructions[param1] * instructions[param2];
            i += 4;
        } else if (opcode == 99) {
            break;
        } else {
            println("ERROR: Unknown opcode: {}", opcode);
            exit(1);
        }
    }
}

std::expected<vector<string>, string> read_file(const string &filename);

int main(void) {
    string filename = "data/input.txt";
    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Filename = '{}'", filename);
        return 1;
    }
    vector<string> file_contents = result.value();

    long part1 = 0;
    long part2 = 0;

    vector<long> instructions;
    std::stringstream ss(file_contents[0]);
    for (long i; ss >> i;) {
        instructions.push_back(i);
        if (ss.peek() == ',') ss.ignore();
    }

    instructions[1] = 12;
    instructions[2] = 2;

    interpret_instructions(instructions);
    part1 = instructions[0];
    assert(part1 == 5866714);

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}

std::expected<vector<string>, string> read_file(const string &filename) {
    std::ifstream file_stream(filename);
    if (!file_stream.is_open())
        return std::unexpected("Failed to open file: " + filename);

    vector<string> file_contents;
    string line;
    while (std::getline(file_stream, line)) file_contents.push_back(std::move(line));
    return file_contents;
}


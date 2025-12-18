#include <cassert>
#include <expected>
#include <sstream>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

struct Instruction {
    long opcode;
    vector<long> params;
    long size;
};

constexpr Instruction ADD = {1, {}, 4};
constexpr Instruction MUL = {2, {}, 4};
constexpr Instruction HALT = {99, {}, 1};

std::optional<Instruction> make_instruction(long ip, vector<long>& memory) {
    long opcode = memory[ip];

    Instruction instr;
    if (opcode == 1) {
        instr = ADD;
        for (int i=1; i<instr.size; i++) instr.params.push_back(memory[ip+i]);
    } else if (opcode == 2) {
        instr = MUL;
        for (int i=1; i<instr.size; i++) instr.params.push_back(memory[ip+i]);
    } else if (opcode == 99) {
        instr = HALT;
    } else {
        return std::nullopt;
    }

    return instr;
}

bool interpret_memory(vector<long>& memory) {
    long i_count = memory.size();

    for (long ip=0; ip<i_count; ) {

        auto instr = make_instruction(ip, memory);
        if (!instr) return false;
        if (instr->opcode == 1) {
            memory[instr->params[2]] = memory[instr->params[0]] + memory[instr->params[1]];
        } else if (instr->opcode == 2) {
            memory[instr->params[2]] = memory[instr->params[0]] * memory[instr->params[1]];
        } else if (instr->opcode == 99) {
            instr = HALT;
            break;
        } else {
            return false;
        }
        ip += instr->size;
    }
    return true;
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

    vector<long> memory;
    std::stringstream ss(file_contents[0]);
    for (long i; ss >> i;) {
        memory.push_back(i);
        if (ss.peek() == ',') ss.ignore();
    }
    vector<long> original_mem = memory;

    memory[1] = 12;
    memory[2] = 2;

    interpret_memory(memory);
    part1 = memory[0];
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


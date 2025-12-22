#include <cassert>
#include <deque>
#include <expected>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

enum InstrType {
    INS_ADD,
    INS_MUL,
    INS_INPUT,
    INS_OUTPUT,
    INS_HALT
};

enum Mode {
    MODE_IM,
    MODE_POS,
};

struct Instruction {
    InstrType type;
    long opcode;
    vector<long> params;
    vector<Mode> modes;
    long size;
};

class Machine {
    std::deque<long> input;
    vector<long> output;
    long ip = 0;
public:
    vector<long> memory;
    void load_mem_from_file(string filename);
    void load_mem_from_string(string string);
    std::optional<Instruction> make_instruction() const;
    void add_input_val(long val);
    bool run();
};

void Machine::add_input_val(long val) {
    input.push_front(val);
}

std::expected<vector<string>, string> read_file(const string &filename);
long size_from_type(InstrType typ);

int main(void) {
    {
        string filename = "../day02/data/input.txt";
        Machine machine;
        machine.load_mem_from_file(filename);
        machine.memory[1] = 12;
        machine.memory[2] = 2;
        machine.run();
        assert(machine.memory[0] == 5866714);
    }

    string filename = "data/input.txt";
    Machine machine;
    machine.load_mem_from_file(filename);
    machine.add_input_val(1);
    machine.run();

    long part1 = 0;
    long part2 = 0;

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

long size_from_type(InstrType typ) {
    switch (typ) {
        case INS_ADD:
        case INS_MUL:
            return 4;
        case INS_INPUT:
        case INS_OUTPUT:
            return 2;
        case INS_HALT:
            return 1;
    }
}

bool Machine::run() {
    ip = 0;

    for (;;) {
        auto instr = make_instruction();
        if (!instr) return false;
        switch (instr->type) {
            case INS_ADD:{
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for the result of addition");
                    return false;
                }
                long op1, op2;
                if (instr->modes[0] == MODE_IM) op1 = instr->params[0];
                else if (instr->modes[0] == MODE_POS) op1 = memory[instr->params[0]];
                else {
                    println("ERROR: Unknown mode type in addition operation");
                    return false;
                }

                if (instr->modes[1] == MODE_IM) op2 = instr->params[1];
                else if (instr->modes[1] == MODE_POS) op2 = memory[instr->params[1]];
                else {
                    println("ERROR: Unknown mode type in addition operation");
                    return false;
                }

                memory[instr->params[2]] = op1 + op2;
            } break;
            case INS_MUL:{
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for the result of multiplication");
                    return false;
                }
                long op1, op2;
                if (instr->modes[0] == MODE_IM) op1 = instr->params[0];
                else if (instr->modes[0] == MODE_POS) op1 = memory[instr->params[0]];
                else {
                    println("ERROR: Unknown mode type in multiplication operation");
                    return false;
                }

                if (instr->modes[1] == MODE_IM) op2 = instr->params[1];
                else if (instr->modes[1] == MODE_POS) op2 = memory[instr->params[1]];
                else {
                    println("ERROR: Unknown mode type in multiplication operation");
                    return false;
                }

                memory[instr->params[2]] = op1 * op2;
            } break;
            case INS_INPUT: {
                if (input.size() <= 0) {
                    println("ERROR: Not enough data in the input vector");
                    return false;
                }
                if (instr->modes[0] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    return false;
                }
                memory[instr->params[0]] = input[0];
                input.pop_front();
            } break;
            case INS_OUTPUT: {
                long op;
                if (instr->modes[0] == MODE_IM) {
                    op = instr->params[0];
                } else if (instr->modes[0] == MODE_POS) {
                    op = memory[instr->params[0]];
                } else {
                    println("ERROR: Unknown mode type in output operation");
                    return false;
                }
                println("OUTPUT: {}", op);
                output.push_back(op);
            } break;
            case INS_HALT: return true;
            default: {
                println("ERROR: Unknown function (code = {})", memory[ip]);
                return false;
            }
        }
        ip += instr->size;
    }
    return true;
}

void Machine::load_mem_from_file(string filename) {
    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Filename = '{}'", filename);
        return;
    }
    vector<string> file_contents = result.value();
    assert(file_contents.size() == 1);

    load_mem_from_string(file_contents[0]);

}

void Machine::load_mem_from_string(string string) {
    std::stringstream ss(string);
    for (long i; ss >> i;) {
        memory.push_back(i);
        if (ss.peek() == ',') ss.ignore();
    }

}

std::optional<Instruction> Machine::make_instruction() const {
    long instrcode = memory[ip];
    long opcode = instrcode % 100;
    instrcode /= 100;

    Instruction instr;
    if (opcode == 1) {
        instr.type = INS_ADD;
    } else if (opcode == 2) {
        instr.type = INS_MUL;
    } else if (opcode == 3) {
        instr.type = INS_INPUT;
    } else if (opcode == 4) {
        instr.type = INS_OUTPUT;
    } else if (opcode == 99) {
        instr.type = INS_HALT;
    } else {
        println("ERROR: Unknown opcode: '{}'", opcode);
        return std::nullopt;
    }

    instr.size = size_from_type(instr.type);
    for (int i=1; i<instr.size; i++) {
        instr.params.push_back(memory[ip+i]);
        if (instrcode % 10 == 0) instr.modes.push_back(MODE_POS);
        else if (instrcode % 10 == 1) instr.modes.push_back(MODE_IM);
        else {
            println("ERROR: Unknown mode: {}", instrcode % 10);
            return std::nullopt;
        }
        instrcode /= 10;
    }

    return instr;
}


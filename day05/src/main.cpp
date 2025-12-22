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
    INS_HALT,
    INS_JIT,
    INS_JIF,
    INS_LT,
    INS_EQ,

    INS_COUNT,
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
    bool controls_ip = false;
    long get_operand(const vector<long> memory, size_t index) const;
};

class Machine {
    std::deque<long> input;
    long ip = 0;
public:
    vector<long> output;
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
    machine_part2.run();
    long part2 = machine_part2.output.back();

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
        case INS_LT:
        case INS_EQ:
            return 4;
        case INS_INPUT:
        case INS_OUTPUT:
            return 2;
        case INS_JIT:
        case INS_JIF:
            return 3;
        case INS_HALT:
            return 1;
        case INS_COUNT:
            println("ERROR: 'INS_COUNT' provided to size_from_type");
            println("This means a bug in the calling code");
            exit(1);
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
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
                memory[instr->params[2]] = op1 + op2;
            } break;
            case INS_MUL:{
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for the result of multiplication");
                    return false;
                }
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
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
                long op = instr->get_operand(memory, 0);
                println("OUTPUT: {}", op);
                output.push_back(op);
            } break;
            case INS_JIF: {
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
                if (op1 == 0) ip = op2;
                else ip += instr->size;
            } break;
            case INS_JIT: {
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
                if (op1 != 0) ip = op2;
                else ip += instr->size;
            } break;
            case INS_LT: {
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    return false;
                }
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
                if (op1 < op2) memory[instr->params[2]] = 1;
                else memory[instr->params[2]] = 0;
            } break;
            case INS_EQ: {
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    return false;
                }
                long op1 = instr->get_operand(memory, 0);
                long op2 = instr->get_operand(memory, 1);
                if (op1 == op2) memory[instr->params[2]] = 1;
                else memory[instr->params[2]] = 0;
            } break;
            case INS_HALT: return true;
            default: {
                println("ERROR: Unknown function (code = {})", memory[ip]);
                return false;
            }
        }
        if (!instr->controls_ip) ip += instr->size;
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
    memory.clear();
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
    if (opcode == 1)       instr.type = INS_ADD;
    else if (opcode == 2)  instr.type = INS_MUL;
    else if (opcode == 3)  instr.type = INS_INPUT;
    else if (opcode == 4)  instr.type = INS_OUTPUT;
    else if (opcode == 5)  {
        instr.type = INS_JIT;
        instr.controls_ip = true;
    }
    else if (opcode == 6)  {
        instr.type = INS_JIF;
        instr.controls_ip = true;
    }
    else if (opcode == 7)  instr.type = INS_LT;
    else if (opcode == 8)  instr.type = INS_EQ;
    else if (opcode == 99) instr.type = INS_HALT;
    else {
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

long Instruction::get_operand(const vector<long> memory, size_t index) const {
    Mode mode = modes[index];
    long param = params[index];

    switch (mode) {
        case MODE_IM: return param;
        case MODE_POS: return memory[param];
    }
}


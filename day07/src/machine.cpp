#include <cassert>
#include <cstdio>
#include <optional>
#include <print>
#include <fstream>
#include <sstream>
#include "machine.hpp"

using std::println;

std::expected<vector<string>, string> read_file(const string &filename) {
    std::ifstream file_stream(filename);
    if (!file_stream.is_open())
        return std::unexpected("Failed to open file: " + filename);

    vector<string> file_contents;
    string line;
    while (std::getline(file_stream, line)) file_contents.push_back(std::move(line));
    return file_contents;
}

Machine::Machine(string filename) {
    this->load_mem_from_file(filename);
}

bool Machine::run() {
    if (memory.size() == 0) {
        println("ERROR: Nothing in memory, so no program to run");
        state = STATE_ERROR;
        return false;
    }
    switch (state) {
        case STATE_FRESH:
        case STATE_HALTED: ip = 0; break;
        case STATE_AWAITING_INPUT: break;
        case STATE_RUNNING:
            println("ERROR: Restarting a running machine shows a bug. Fix your code");
            exit(1);
        case STATE_ERROR:
            println("Restarting a machine in an error condition is not wise!");
            exit(1);
    }
    state = STATE_RUNNING;

    for (;;) {
        auto instr = make_instruction();
        if (!instr) {
            state = STATE_ERROR;
            return false;
        }
        switch (instr->type) {
            case INS_ADD:{
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for the result of addition");
                    state = STATE_ERROR;
                    return false;
                }
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                memory[instr->params[2]] = *op1 + *op2;
            } break;
            case INS_MUL:{
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for the result of multiplication");
                    state = STATE_ERROR;
                    return false;
                }
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                memory[instr->params[2]] = *op1 * *op2;
            } break;
            case INS_INPUT: {
                if (input.size() <= 0) {
                    state = STATE_AWAITING_INPUT;
                    return true;
                }
                if (instr->modes[0] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    state = STATE_ERROR;
                    return false;
                }
                memory[instr->params[0]] = input[0];
                input.pop_front();
            } break;
            case INS_OUTPUT: {
                auto op = instr->get_operand(memory, 0);
                // println("OUTPUT: {}", op);
                if (!op) {
                    state = STATE_ERROR;
                    return false;
                }
                output.push_back(*op);
            } break;
            case INS_JIF: {
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                if (*op1 == 0) ip = *op2;
                else ip += instr->size;
            } break;
            case INS_JIT: {
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                if (*op1 != 0) ip = *op2;
                else ip += instr->size;
            } break;
            case INS_LT: {
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    state = STATE_ERROR;
                    return false;
                }
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                if (*op1 < *op2) memory[instr->params[2]] = 1;
                else memory[instr->params[2]] = 0;
            } break;
            case INS_EQ: {
                if (instr->modes[2] == MODE_IM) {
                    println("ERROR: Immediate mode not appropriate for storing data");
                    state = STATE_ERROR;
                    return false;
                }
                auto op1 = instr->get_operand(memory, 0);
                auto op2 = instr->get_operand(memory, 1);
                if (!op1 || !op2) {
                    state = STATE_ERROR;
                    return false;
                }
                if (*op1 == *op2) memory[instr->params[2]] = 1;
                else memory[instr->params[2]] = 0;
            } break;
            case INS_HALT:
                state = STATE_HALTED;
                return true;
            default: {
                println("ERROR: Unknown function (code = {})", memory[ip]);
                state = STATE_ERROR;
                return false;
            }
        }
        if (!instr->controls_ip) ip += instr->size;
    }
    assert(0 && "Unreachable!");
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

    instr.size = instr.size_from_type();
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

void Machine::add_input_val(long val) {
    input.push_front(val);
}

std::optional<long> Instruction::get_operand(const vector<long> memory, size_t index) const {
    Mode mode = modes[index];
    long param = params[index];

    switch (mode) {
        case MODE_IM: return param;
        case MODE_POS: {
            if (param < (long)memory.size()) return memory[param];
            else return std::nullopt;
        }
    }
}

long Instruction::size_from_type() const {
    switch (type) {
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


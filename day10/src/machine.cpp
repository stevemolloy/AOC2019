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

long Memory::length() const {
    return _memory.size();
}

long Memory::write(long loc, long val) {
    if (length() <= loc) {
        _extend_memory(loc + 1);
    }
    _memory[loc] = val;
    return _memory[loc];
}

long Memory::write_rel(long loc, long val) {
    loc += rel_base;
    if (length() <= loc) {
        _extend_memory(loc + 1);
    }
    _memory[loc] = val;
    return _memory[loc];
}

long Memory::read(long loc) {
    if (length() <= loc) {
        _extend_memory(loc + 1);
    }
    return _memory[loc];
}

long Memory::read_rel(long loc) {
    loc += rel_base;
    if (length() <= loc) {
        _extend_memory(loc + 1);
    }
    return _memory[loc];
}

void Memory::zero() {
    size_t N = length();
    for (size_t i=0; i<N; i++) {
        _memory[i] = 0;
    }
}

long Memory::append(long val) {
    _memory.push_back(val);
    return _memory.back();
}

void Memory::adjust_relbase(long offs) {
    rel_base += offs;
}

long Memory::_extend_memory(long new_size) {
    long N = length();
    if (new_size <= N) return N;
    println("WARN: Extending memory from {} to {}", N, new_size);
    _memory.resize(new_size);
    return length();
}

Machine::Machine(string filename) {
    this->load_mem_from_file(filename);
}

bool Machine::run() {
    if (memory.length() == 0) {
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
                if (instr->modes[2] == MODE_POS)      memory.write(instr->params[2], *op1 + *op2);
                else if (instr->modes[2] == MODE_REL) memory.write_rel(instr->params[2], *op1 + *op2);
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
                if (instr->modes[2] == MODE_POS)      memory.write(instr->params[2], *op1 * *op2);
                else if (instr->modes[2] == MODE_REL) memory.write_rel(instr->params[2], *op1 * *op2);
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
                if (instr->modes[0] == MODE_POS)      memory.write(instr->params[0], input[0]);
                else if (instr->modes[0] == MODE_REL) memory.write_rel(instr->params[0], input[0]);
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
                if (instr->modes[2] == MODE_POS) {
                    if (*op1 < *op2) memory.write(instr->params[2], 1);
                    else memory.write(instr->params[2], 0);
                } else if (instr->modes[2] == MODE_REL) {
                    if (*op1 < *op2) memory.write_rel(instr->params[2], 1);
                    else memory.write_rel(instr->params[2], 0);
                }
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
                if (instr->modes[2] == MODE_POS) {
                    if (*op1 == *op2) memory.write(instr->params[2], 1);
                    else memory.write(instr->params[2], 0);
                } else if (instr->modes[2] == MODE_REL) {
                    if (*op1 == *op2) memory.write_rel(instr->params[2], 1);
                    else memory.write_rel(instr->params[2], 0);
                }
            } break;
            case INS_HALT:
                state = STATE_HALTED;
                return true;
            case INS_RELBASE: {
                auto op = instr->get_operand(memory, 0);
                if (!op) {
                    state = STATE_ERROR;
                    return false;
                }
                memory.adjust_relbase(*op);
            } break;
            default: {
                println("ERROR: Unknown function (code = {})", memory.read(ip));
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
    memory.zero();
    std::stringstream ss(string);
    for (long i; ss >> i;) {
        memory.append(i);
        if (ss.peek() == ',') ss.ignore();
    }
}

std::optional<Instruction> Machine::make_instruction() {
    long instrcode = memory.read(ip);
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
    else if (opcode == 9)  instr.type = INS_RELBASE;
    else if (opcode == 99) instr.type = INS_HALT;
    else {
        println("ERROR: Unknown opcode: '{}'", opcode);
        return std::nullopt;
    }

    instr.size = instr.size_from_type();
    for (int i=1; i<instr.size; i++) {
        instr.params.push_back(memory.read(ip+i));
        if (instrcode % 10 == 0) instr.modes.push_back(MODE_POS);
        else if (instrcode % 10 == 1) instr.modes.push_back(MODE_IM);
        else if (instrcode % 10 == 2) instr.modes.push_back(MODE_REL);
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

std::optional<long> Instruction::get_operand(Memory& memory, size_t index) {
    Mode mode = modes[index];
    long param = params[index];

    switch (mode) {
        case MODE_IM: return param;
        case MODE_POS: {
            return memory.read(param);
        }
        case MODE_REL:
            return memory.read_rel(param);
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
        case INS_RELBASE:
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

long drive_amp_chain_cont(vector<Machine>& amp_chain, const vector<long>& phases, long input) {
    input = drive_amp_chain(amp_chain, phases, input);
    for (;;) {
        long new_input = drive_amp_chain(amp_chain, {}, input);
        if (new_input == input) break;
        input = new_input;
    }
    return input;
}

long drive_amp_chain(vector<Machine>& amp_chain, const vector<long>& phases, long input) {
    for (long i=0; Machine& amp: amp_chain) {
        amp.add_input_val(input);
        if (phases.size() > 0)
            amp.add_input_val(phases.at(i));
        amp.run();
        if (amp.output.size() == 0) {
            break;
        }
        input = amp.output.front();
        amp.output.pop_front();
        i += 1;
    }
    return input;
}


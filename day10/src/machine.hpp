#include <vector>
#include <deque>
#include <string>
#include <optional>
#include <expected>

using std::vector;
using std::string;

std::expected<vector<string>, string> read_file(const string &filename);

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
    INS_RELBASE,

    INS_COUNT,
};

enum Mode {
    MODE_IM,
    MODE_POS,
    MODE_REL,
};

class Memory {
private:
    vector<long> _memory;
    long rel_base = 0;
    long _extend_memory(long new_size);

public:
    Memory() =default;
    Memory(string filename);

    long length() const;
    long read(long loc);
    long read_rel(long loc);

    void adjust_relbase(long loc);
    void zero();
    long write(long loc, long val);
    long write_rel(long loc, long val);
    long append(long val);
};

struct Instruction {
    InstrType type;
    long opcode;
    vector<long> params;
    vector<Mode> modes;
    long size;
    bool controls_ip = false;
    std::optional<long> get_operand(Memory& memory, size_t index);
    long size_from_type() const;
};

enum MachineState {
    STATE_FRESH,
    STATE_RUNNING,
    STATE_AWAITING_INPUT,
    STATE_HALTED,
    STATE_ERROR,
};

class Machine {
public:
    Machine() =default;
    Machine(string filename);
    MachineState state = STATE_FRESH;
    std::deque<long> input;
    long ip = 0;
    std::deque<long> output;
    Memory memory;
    void load_mem_from_file(string filename);
    void load_mem_from_string(string string);
    std::optional<Instruction> make_instruction();
    void add_input_val(long val);
    bool run();
};

long drive_amp_chain(vector<Machine>& amp_chain, const vector<long>& phases, long input);
long drive_amp_chain_cont(vector<Machine>& amp_chain, const vector<long>& phases, long input);


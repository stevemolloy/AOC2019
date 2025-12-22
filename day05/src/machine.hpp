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
    long size_from_type() const;
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



#include <algorithm>
#include <cassert>
#include <cmath>
#include <expected>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

struct Password {
    long input;
    vector<int> digits;
    Password(long pass);
    bool check() const;
    bool check_limited() const;
    bool all_rising() const;
    bool duplicates() const;
    bool dupes_limited() const;
};

Password::Password(long pass) : input(pass) {
    assert(pass < 1000*1000);
    for (int i=5; i>=0; i--) {
        digits.push_back(pass / (long)std::pow(10, i));
        pass = pass % (long)std::powl(10, i);
    }
}

bool Password::check() const {
    if (all_rising() && duplicates()) return true;
    return false;
}

bool Password::all_rising() const {
    vector<int> s_digits = digits;
    std::sort(s_digits.begin(), s_digits.end());
    return s_digits == digits;
}

bool Password::duplicates() const {
    return (digits[0] == digits[1] || digits[1] == digits[2] || digits[2] == digits[3] || digits[3] == digits[4] || digits[4] == digits[5]);
}

bool Password::dupes_limited() const {
    if (digits[0] == digits[1] && digits[1] != digits[2]) return true;
    if (digits[0] != digits[1] && digits[1] == digits[2] && digits[2] != digits[3]) return true;
    if (digits[1] != digits[2] && digits[2] == digits[3] && digits[3] != digits[4]) return true;
    if (digits[2] != digits[3] && digits[3] == digits[4] && digits[4] != digits[5]) return true;
    if (digits[3] != digits[4] && digits[4] == digits[5]) return true;
    return false;
}

bool Password::check_limited() const {
    if (all_rising() && dupes_limited()) return true;
    return false;
}

std::expected<vector<string>, string> read_file(const string &filename);

int main(void) {
    {
        Password test1(111111);
        assert(test1.check());
        Password test2(223450);
        assert(!test2.all_rising());
        assert(test2.duplicates());
        assert(!test2.check());
        Password test3(123789);
        assert(test3.all_rising());
        assert(!test3.duplicates());
        assert(!test3.check());
        Password test4(112233);
        assert(test4.check_limited());
        Password test5(123444);
        assert(test5.all_rising());
        assert(!test5.check_limited());
        Password test6(111122);
        assert(test6.check_limited());
    }
    
    long first = 134792;
    long last  = 675810;

    long part1 = 0;
    long part2 = 0;
    for (long val = first; val<=last; val++) {
        Password pass(val);
        if (pass.check()) part1 += 1;
        if (pass.check_limited()) {
            println("Pass: {}", pass.input);
            part2 += 1;
        }
    }

    println("Part 1: {}", part1);
    // 1749 is too high
    println("Part 2: (1749 is too high) {}", part2);

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


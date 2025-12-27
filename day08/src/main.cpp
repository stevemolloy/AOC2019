#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cstddef>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;
using std::array;

template<std::size_t SIZE>
int count_vals(array<int, SIZE> arr, int val);

constexpr int NUMLEVELS = 100;
constexpr int NUMPIXELS = 25 * 6;

int main(void) {
    string filename = "data/input.txt";

    auto file_read = read_file(filename);
    if (!file_read) {
        println("ERROR: Could not read file");
        return 1;
    }
    vector<string> file_contents = *file_read;
    assert(file_contents.size() == 1);
    string input_data = file_contents[0];

    array<array<int, NUMPIXELS>, NUMLEVELS> levels;
    for (int level=0; level<NUMLEVELS; level++) {
        for (int pixel=0; pixel<NUMPIXELS; pixel++) {
            levels[level][pixel] = input_data[NUMPIXELS*level + pixel] - '0';
        }
    }

    array<int, NUMLEVELS> count_zeros;
    for (int i=0; const auto& level: levels)
        count_zeros[i++] = count_vals(level, 0);

    int min_zero_count = INT_MAX;
    int min_zero_index = 0;
    for (int i=0; auto val : count_zeros) {
        if (val < min_zero_count) {
            min_zero_count = val;
            min_zero_index = i;
        }
        i += 1;
    }
    println("{} ==> {}", min_zero_index, min_zero_count);
    int ones = count_vals(levels[min_zero_index], 1);
    int twos = count_vals(levels[min_zero_index], 2);

    long part1 = ones * twos;
    if (filename == "data/input.txt") assert(part1 = 1463);
    long part2 = 0;

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}

template<std::size_t SIZE>
int count_vals(array<int, SIZE> arr, int cmp) {
    int result = 0;
    for (auto val: arr) {
        if (val == cmp) result += 1;
    }
    return result;
}


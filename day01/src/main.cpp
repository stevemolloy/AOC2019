#include <cassert>
#include <charconv>
#include <expected>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

std::expected<vector<string>, string> read_file(const string &filename);

long fuel_from_mass(long mass) {
    return (mass / 3 ) - 2;
}

int main(void) {
    assert(fuel_from_mass(12) == 2);
    assert(fuel_from_mass(100756) == 33583);
    string filename = "data/input.txt";
    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Filename = '{}'", filename);
        return 1;
    }
    vector<string> file_contents = result.value();

    long total_fuel = 0;
    for (const auto& line: file_contents) {
        long mass;
        std::from_chars(line.data(), line.data() + line.size(), mass);
        total_fuel += fuel_from_mass(mass);
    }

    long part1 = total_fuel;
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


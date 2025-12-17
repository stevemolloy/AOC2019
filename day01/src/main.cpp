#include <cassert>
#include <charconv>
#include <climits>
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
    long fuel = (mass / 3 ) - 2;
    return fuel >= 0 ? fuel : 0;
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

    long part1 = 0;
    long part2 = 0;
    for (const auto& line: file_contents) {
        long mass;
        std::from_chars(line.data(), line.data() + line.size(), mass);
        part1 += fuel_from_mass(mass);

        long new_fuel = fuel_from_mass(mass);
        long starting_mass = mass;
        while (new_fuel > 0) {
            mass += new_fuel;
            new_fuel = fuel_from_mass(new_fuel);
        }

        part2 += mass - starting_mass;
    }

    assert(part1 == 3512133);
    assert(part2 == 5265294);

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


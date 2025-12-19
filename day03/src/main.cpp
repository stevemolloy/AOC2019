#include <algorithm>
#include <cassert>
#include <charconv>
#include <climits>
#include <cstdlib>
#include <expected>
#include <sstream>
#include <string>
#include <vector>
#include <print>
#include <fstream>

using std::println;
using std::vector;
using std::string;

using Cell = vector<long>;

void print_cell(Cell cell) {
    for (const long& val : cell)
        std::print("{}, ", val);
}

std::vector<Cell> findCommon(std::vector<Cell> vec1, std::vector<Cell> vec2) {
    // Sort both vectors first (required for set_intersection)
    std::ranges::sort(vec1);
    std::ranges::sort(vec2);
    
    std::vector<Cell> result;
    std::ranges::set_intersection(vec1, vec2, std::back_inserter(result));
    
    return result;
}

struct Move {
    enum {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
    } dir;
    long dist;

    Move(char c, long dist);
    void apply(vector<Cell>& path) const;
};

Move::Move(char c, long dist) : dist(dist) {
    if (c=='R') dir = MOVE_RIGHT;
    else if (c=='L') dir = MOVE_LEFT;
    else if (c=='U') dir = MOVE_UP;
    else if (c=='D') dir = MOVE_DOWN;
    else {
        println("ERROR: Unexpected char: '{}'", c);
        exit(1);
    }
}

void Move::apply(vector<Cell>& path) const {
    Cell loc;
    if (path.size() > 0) loc = path.back();
    else loc = {0, 0};
    for (long i=0; i<dist; i++) {
        switch (dir) {
            case Move::MOVE_LEFT:  loc[0] -= 1; break;
            case Move::MOVE_RIGHT: loc[0] += 1; break;
            case Move::MOVE_DOWN:  loc[1] -= 1; break;
            case Move::MOVE_UP:    loc[1] += 1; break;
            default:
                println("ERROR: Memory corruption!");
                exit(1);
        }
        path.push_back(loc);
    }
}

std::expected<vector<string>, string> read_file(const string &filename);

int main(void) {
    // string filename = "data/test1.txt";
    // string filename = "data/test2.txt";
    // string filename = "data/test3.txt";
    string filename = "data/input.txt";
    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Filename = '{}'", filename);
        return 1;
    }
    vector<string> file_contents = result.value();

    vector<Move> dirs[2];
    for (int i=0; const auto& line: file_contents) {
        std::stringstream ss(line);
        for (string chunk; std::getline(ss, chunk, ',');) {
            std::string_view sv(chunk);
            long dist;
            char c = chunk[0];
            sv.remove_prefix(1);
            std::from_chars(sv.data(), sv.data()+sv.size(), dist);

            dirs[i].emplace_back(c, dist);
        }
        i += 1;
    }

    vector<Cell> paths[2];
    paths[0].reserve(dirs[0].size());
    paths[1].reserve(dirs[1].size());

    Cell loc = {0,0};
    // paths[0].push_back(loc);
    for (const Move& dir: dirs[0])
        dir.apply(paths[0]);

    loc = {0,0};
    // paths[1].push_back(loc);
    for (const Move& dir: dirs[1])
        dir.apply(paths[1]);

    // println("------------------------------");
    // for (const auto& loc: paths[0]) {
    //     for (auto val: loc) std::print("{}, ", val);
    //     println("");
    // }
    // println("------------------------------");
    // for (const auto& loc: paths[1]) {
    //     for (auto val: loc) std::print("{}, ", val);
    //     println("");
    // }
    // println("------------------------------");

    vector<Cell> common = findCommon(paths[0], paths[1]);
    long mindist = LONG_MAX;
    for (const auto& loc: common) {
        long dist = std::abs(loc[0]) + std::abs(loc[1]);
        if (dist < mindist) mindist = dist;
    }

    long part1 = mindist;

    long min_pathlen = LONG_MAX;
    for (const auto& cell2test : common) {
        long path1len = 0, path2len = 0;
        for (size_t i=0; i<paths[0].size(); i++) {
            if (cell2test == paths[0][i]) {
                path1len = i+1;
                break;
            }
        }
        assert(path1len != 0);
        for (size_t i=0; i<paths[1].size(); i++) {
            if (cell2test == paths[1][i]) {
                path2len = i+1;
                break;
            }
        }
        assert(path2len != 0);
        long pathlen = path1len + path2len;
        if (pathlen < min_pathlen) min_pathlen = pathlen;
    }

    long part2 = min_pathlen;

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


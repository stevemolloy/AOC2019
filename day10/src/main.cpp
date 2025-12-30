#include <cassert>
#include <format>
#include <set>
#include <string>
#include <print>

#include "machine.hpp"

using std::println;
using std::string;

class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point(const Point&& other) : x(std::move(other.x)), y(std::move(other.y)) {}

    [[nodiscard]] bool operator== (Point other) const {
        return (x == other.x && y == other.y);
    }
    [[nodiscard]] bool operator<(Point other) const {
        return (x == other.x) ? y < other.y : x < other.x;
    }
    [[nodiscard]] bool operator>(Point other) const {
        return (x == other.x) ? y > other.y : x > other.x;
    }
    [[nodiscard]] Point operator-(Point other) const {
        return Point(x - other.x, y-other.y);
    }

    void reduce() {
        int maxval = (abs(x) > abs(y)) ? abs(x) : abs(y);

        for (int i=2; i<=maxval; i++) {
            while (x%i==0 && y%i==0) {
                x /= i;
                y /= i;
            }
        }
    }
};

template<>
struct std::formatter<Point> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Point& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Point({}, {})", p.x, p.y);
    }
};

int main(void) {
    // string filename = "data/test1.txt";
    // string filename = "data/test2.txt";
    // string filename = "data/test3.txt";
    // string filename = "data/test4.txt";
    // string filename = "data/test5.txt";
    string filename = "data/input.txt";

    auto result = read_file(filename);
    if (!result) {
        println("ERROR: Could not read file '{}'", filename);
        return 1;
    }
    vector<string> file_contents = *result;

    int grid_height = file_contents.size();
    assert(grid_height > 0);
    int grid_width = file_contents[0].size();

    vector<Point> points;
    points.reserve(grid_height * grid_width);
    for (int i=0; i<grid_height; i++) {
        for (int j=0; j<grid_width; j++) {
            if (file_contents[i][j] == '#') points.emplace_back(j, i);
        }
    }

    long part1 = 0;
    int asteroid_N = points.size();
    std::set<Point> ray_set;
    for (int i=0; i<asteroid_N; i++) {
        ray_set.clear();
        for (int j=0; j<asteroid_N; j++) {
            if (i==j) continue;
            Point diff = points[j] - points[i];
            diff.reduce();
            ray_set.insert(diff);
        }

        int visible = ray_set.size();
        if (visible > part1) part1 = visible;
    }
    if (filename == "data/input.txt") assert(part1 == 347);
    if (filename == "data/test1.txt") assert(part1 == 8);

    long part2 = 0;

    println("Part 1: {}", part1);
    println("Part 2: {}", part2);

    return 0;
}


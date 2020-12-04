#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

constexpr char tree = '#';

struct traject_pace_t {
    int x;
    int y;
};

std::vector<std::string> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::vector<std::string> all_lines;
    std::string line;
    while (std::getline(is, line)) {
        all_lines.push_back(line);
    }
    return all_lines;
}

int TreesEncounteredTerrain(const std::vector<std::string>& terrain, traject_pace_t pace) {
    int trees_encountered = 0;
    int x = 0; 
    int repeat_x_coordinate = terrain[0].size();
    for (int y = 0; y < terrain.size(); y += pace.y) {
        char coordinate = terrain[y].at(x % repeat_x_coordinate);
        if (coordinate == tree)
            trees_encountered += 1;
        x += pace.x;
    }
    return trees_encountered;
}

int main() {
    auto toboggan_terrain = CreateVectorFromFile("input.txt");
    std::vector<traject_pace_t> paces = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    long multi_trees = 1;
    for (const traject_pace_t& p: paces)
        multi_trees *= TreesEncounteredTerrain(toboggan_terrain, p);
    std::cout << multi_trees << "\n";
    return 0;
}

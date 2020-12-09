#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <cmath>

std::vector<std::string> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::string line;
    std::vector<std::string> all_lines;
    while (std::getline(is, line)) {
        all_lines.push_back(line);
    }
    return all_lines;
}

int FindBinary(const std::string& str, char lower, char upper, int min, int max) {
    for (const char& c: str) {
        int diff = max - min;
        int halver = ceil(diff / 2.0);
        if (c == upper)
            max -= halver;
        if (c == lower)
            min += halver;
    }
    return max;
}


int FindRow(const std::string& boarding_pass_sequence) {
    return FindBinary(boarding_pass_sequence, 'B', 'F', 0, 127);
}

int FindColumn(const std::string& boarding_pass_sequence) {
    return FindBinary(boarding_pass_sequence, 'R', 'L', 0, 7);
}

int GetSeatId(const std::string& boarding_pass) {
    return FindRow(boarding_pass) * 8 + FindColumn(boarding_pass);
}

std::vector<int> GetAllSeatId(const std::vector<std::string>& boarding_passes) {
    std::vector<int> seat_ids = {};
    for (const auto& bp: boarding_passes) {
        int seat_id = GetSeatId(bp);
        seat_ids.push_back(seat_id);
    }
    return seat_ids;
}

int FindHighestSeatId(const std::vector<std::string>& boarding_passes) {
    int highest = 0;
    for (const auto& bp: boarding_passes) {
        int seat_id = GetSeatId(bp);
        if (seat_id > highest)
            highest = seat_id;
    }
    return highest;
}

int main() {
    std::string test1 = "BFFFBBFRRR";
    std::string test2 = "FFFBBBFRRR";
    std::string test3 = "BBFFBBFRLL";

    std::cout << GetSeatId(test1) << "\n";
    std::cout << GetSeatId(test2) << "\n";
    std::cout << GetSeatId("BFFFFFBRLL") << "\n";

    auto boarding_passes = CreateVectorFromFile("input.txt");
    std::cout << "Highest seat ID: " << FindHighestSeatId(boarding_passes) << "\n";
    auto ids = GetAllSeatId(boarding_passes);
    std::sort(ids.begin(), ids.end());
    int start_seat_id = ids[0];
    std::cout << "Start seat id: " << start_seat_id << "\n";
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] != start_seat_id + i) {
            std::cout << start_seat_id + i << "\n";
            break;
        }
    }

    return 0;
}

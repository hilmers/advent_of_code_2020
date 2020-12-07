#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

constexpr std::vector<std::string> mandatory_fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"];

std::vector<std::string> Split(const std::string& str, char delimiter) {
     std::vector<std::string> split_strings{};
     std::stringstream ss(str);
     for (std::string substring; std::getline(ss, substring, delimiter); split_strings.push_back(substring));
     return split_strings;
}

std::vector<std::unordered_map<std::string, std::string>> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::vector<std::unordered_map<std::string, std::string>> all_passports;
    std::string line;
    std::unordered_map<std::string, std::string> passport = {};
    while (std::getline(is, line)) {
        if (line.empty()) {
            all_passports.push_back(passport);
            passport = {};
            continue;
        }
        auto fields = Split(line, ' ');
        for (const auto& field: fields) {
            auto vals = Split(field, ':');
            std::cout << vals.front() << " : " << vals.back() << "\n";
            passport[vals.front()] = vals.back();
        }
    }
    all_passports.push_back(passport);
    return all_passports;
}

int main() {
    auto passports = CreateVectorFromFile("example.txt");
    int valid_passes = 0;
    for (const auto& mf: mandatory_fields) {
        if (

    std::cout << valid_passes << "\n";
    return 0;
}

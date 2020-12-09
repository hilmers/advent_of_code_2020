#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>

const std::vector<std::string> kMandatoryFields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
typedef std::unordered_map<std::string, std::string> passport;

std::vector<std::string> Split(const std::string& str, char delimiter) {
     std::vector<std::string> split_strings{};
     std::stringstream ss(str);
     for (std::string substring; std::getline(ss, substring, delimiter); split_strings.push_back(substring));
     return split_strings;
}

std::vector<passport> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::vector<passport> all_passports;
    std::string line;
    passport p = {};
    while (std::getline(is, line)) {
        if (line.empty()) {
            all_passports.push_back(p);
            p = {};
            continue;
        }
        auto fields = Split(line, ' ');
        for (const auto& field: fields) {
            auto vals = Split(field, ':');
            p[vals.front()] = vals.back();
        }
    }
    return all_passports;
}

bool DataInRange(const std::string& data, int lower, int upper) {
    int d = stoi(data);
    if (d >= lower && d <= upper)
        return true;
    return false;
}

bool DataIsValid(const std::string& field, const std::string& data) {
    if (field == "byr") {
        return DataInRange(data, 1920, 2020);
    } else if (field == "iyr") {
        return DataInRange(data, 2010, 2020);
    } else if (field  == "eyr") {
        return DataInRange(data, 2020, 2030);
    } else if (field == "hgt") {
        std::string height = std::regex_replace(data, std::regex("[^0-9]*([0-9]+).*"), std::string("$1"));
        if (std::regex_search(data, std::regex("(cm)"))) {
            return DataInRange(height, 150, 193);
        } else if (std::regex_search(data, std::regex("(in)"))) {
            return DataInRange(height, 59, 76);
        } else {
            return false;
        }
    } else if (field == "hcl") {
        return std::regex_search(data, std::regex("^#([a-f0-9]{6})$"));
    } else if (field == "ecl") {
        return std::regex_search(data, std::regex("^(amb|blu|brn|gry|grn|hzl|oth)$"));
    } else if (field == "pid") {
        return std::regex_search(data, std::regex("^([0-9]{9})$"));
    }
}

bool MandatoryFieldsAreValid(passport p) {
    for (const auto& mf: kMandatoryFields) {
        if (p.find(mf) == p.end())
            return false;
        if (!DataIsValid(mf, p[mf]))
            return false;
    }
    return true;
}

bool AllMandatoryFieldsPresent(const passport& p) {
    for (const auto& mf: kMandatoryFields) {
        if (p.find(mf) == p.end())
            return false;
    }
    return true;
}

std::vector<passport> GetValidPassports(const std::vector<passport>& passports) {
    std::vector<passport> valid_passports;
    for (const auto& p: passports) {
        if (MandatoryFieldsAreValid(p))
            valid_passports.push_back(p);
    }
    return valid_passports;
}

int main() {
    auto passports = CreateVectorFromFile("input.txt");
    auto valid_passes = GetValidPassports(passports);
    // bool ok = DataIsValid("pid", "00001234");
    std::cout << "Valid passports: " << valid_passes.size() << "\n";
    return 0;
}

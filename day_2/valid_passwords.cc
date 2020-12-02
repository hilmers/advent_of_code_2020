#include <algorithm>
#include <locale>
#include <fstream>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

std::vector<std::string> Split(const std::string& str, char delimiter) {
     std::vector<std::string> split_strings{};
     std::stringstream ss(str);
     for (std::string substring; std::getline(ss, substring, delimiter); split_strings.push_back(substring));
     return split_strings;
}

std::vector<std::string> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::vector<std::string> all_lines;
    std::string line;
    while (std::getline(is, line)) {
        all_lines.push_back(line);
    }
    return all_lines;
}

std::vector<std::string> GetPasswordAndPolicy(const std::string& policy_and_password) {
    auto policy_password_split = Split(policy_and_password, ':');
    std::string password = policy_password_split.back();
    std::string::iterator end_pos = std::remove(password.begin(), password.end(), ' ');
    password.erase(end_pos, password.end());
    policy_password_split.back() = password;
    return policy_password_split;
}

std::vector<int> GetRange(const std::string& policy) {
    std::string defined_range = Split(policy, ' ').front();
    auto range = Split(defined_range, '-');
    int min = std::stoi(range.front());
    int max = std::stoi(range.back());
    return {min, max};
}

int NumberOfValidPasswords(const std::vector<std::string>& policy_and_passwords) {
    int valid_pass = 0;
    for (int i = 0; i < policy_and_passwords.size(); ++i) {
        auto pap = GetPasswordAndPolicy(policy_and_passwords[i]);
        auto policy = pap.front();
        auto password = pap.back();
        char policy_char = policy.back();
        int occurences = count(password.begin(), password.end(), policy_char);
        auto range = GetRange(policy);
        std::cout << "Min: " << range.front() << " Max: " << range.back() << " Occurences: " << occurences << "\n";
        if (range.front() <= occurences && occurences <= range.back()) {
            std::cout << "VALID!\n";
            valid_pass += 1;
        }
    }
    return valid_pass;
}

int NumberOfValidPasswordsTwo(const std::vector<std::string>& policy_and_passwords) {
    int valid_pass = 0;
    for (int i = 0; i < policy_and_passwords.size(); ++i) {
        auto pap = GetPasswordAndPolicy(policy_and_passwords[i]);
        auto policy = pap.front();
        auto password = pap.back();
        char policy_char = policy.back();
        auto indexes = GetRange(policy);
        std::cout << "First: " << password.at(indexes.front() - 1) << " Last: " << password.at(indexes.back() - 1) << "\n";
        if (password.at(indexes.front() - 1) == policy_char && password.at(indexes.back() - 1) != policy_char) {
            std::cout << "VALID!\n";
            valid_pass += 1;
        }
    }
    return valid_pass;
}

int main() {
    std::vector<std::string> paps = {"1-3 a: abcde", "1-3 b: cdefg", "2-9 c: ccccccccc"};
    std::vector<std::string> passwords_input = CreateVectorFromFile("input.txt");
    int valids = NumberOfValidPasswordsTwo(passwords_input);
    // int valids = NumberOfValidPasswordsTwo(paps);
    std::cout << "Valid passwords: " << valids << "\n";
}

#include <algorithm>
#include <locale>
#include <fstream>
#include <iterator>
#include <iostream>
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

std::string RemoveWhiteSpace(const std::string& password) {
    std::string::iterator end_pos = std::remove(password.begin(), password.end(), ' ');
    password.erase(end_pos, password.end());
    // Password is now cleaned of white spaces
    return password;
}

std::vector<std::string> GetPasswordAndPolicy(const std::string& policy_and_password) {
    auto policy_password_split = Split(policy_and_password, ':');
    std::string dirty_password = policy_password_split.back();
    std::string password = RemoveWhiteSpace(dirty_password);
    return policy_password_split;
}

std::vector<int> GetRange(const std::string& policy) {
    std::string defined_range = Split(policy, ' ').front();
    auto range = Split(defined_range, '-');
    int min = std::stoi(range.front());
    int max = std::stoi(range.back());
    return {min, max};
}

int ValidPasswordsOccurenceCheck(const std::vector<std::string>& policy_and_passwords) {
    int valid_pass = 0;
    for (int i = 0; i < policy_and_passwords.size(); ++i) {
        auto pap = GetPasswordAndPolicy(policy_and_passwords[i]);
        auto policy = pap.front();
        auto password = pap.back();
        char policy_char = policy.back();
        int occurences = count(password.begin(), password.end(), policy_char);
        auto range = GetRange(policy);
        if (range.front() <= occurences && occurences <= range.back()) {
            valid_pass += 1;
        }
    }
    return valid_pass;
}

int ValidPasswordsFixedCharacters(const std::vector<std::string>& policy_and_passwords) {
    int valid_pass = 0;
    for (int i = 0; i < policy_and_passwords.size(); ++i) {
        auto pap = GetPasswordAndPolicy(policy_and_passwords[i]);
        auto policy = pap.front();
        auto password = pap.back();
        char policy_char = policy.back();
        auto indexes = GetRange(policy);

        char first_char = password.at(indexes.front() - 1);
        char second_char = password.at(indexes.back() - 1);
        if (first_char == policy_char && second_char != policy_char) {
            valid_pass += 1;
        } else if (first_char != policy_char && second_char == policy_char) {
            valid_pass += 1;
        }
    }
    return valid_pass;
}

int main() {
    std::vector<std::string> passwords_input = CreateVectorFromFile("input.txt");
    int occurence_check_result = ValidPasswordsOccurenceCheck(passwords_input);
    int fixed_check_result = ValidPasswordsFixedCharacters(passwords_input);
    // int valids = NumberOfValidPasswordsTwo(paps);
    std::cout << "1: " << occurence_check_result << "\n2: " << fixed_check_result << "\n";
}

#include <fstream>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>

constexpr int kTwentyKTwenty = 2020;

std::vector<int> createVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::istream_iterator<int> start(is), end;
    std::vector<int> expenses(start, end);
    return expenses;
}

int multipliedSumOfTwo(const std::vector<int>& input) {
    // Key is the number missing from input for addition to be 2020
    std::unordered_map<int, int> input_missing_mapper = {};
    for (int i = 0; i < input.size(); ++i) {
        if (input_missing_mapper.find(input[i]) != input_missing_mapper.end()) {
            return input[i] * input_missing_mapper[input[i]];
        }
        int sum_short_of_magic_number = kTwentyKTwenty - input[i];
        input_missing_mapper[sum_short_of_magic_number] = input[i];
    }
    // Didn't find a solution in provided input
    return -1;
}

int multipliedSumOfThree(const std::vector<int>& input) {
    std::unordered_map<int, std::vector<int>> input_missing_mapper;
    for (int i = 0; i < input.size(); ++i) {
        if (input_missing_mapper.find(input[i]) != input_missing_mapper.end()) {
            return input[i] * input_missing_mapper[input[i]][0] * input_missing_mapper[input[i]][1];
        }
        for (int j = i + 1; j < input.size(); ++j) {
            int sum_short_of_magic_number = kTwentyKTwenty - input[i] - input[j];
            input_missing_mapper[sum_short_of_magic_number] = {input[i], input[j]};
        }
    }
    // Didn't find a solution in provided input
    return -1;
}

int main() {
    std::vector<int> expenses_input = createVectorFromFile("input.txt");
    int result_two = multipliedSumOfTwo(expenses_input);
    int result_three = multipliedSumOfThree(expenses_input);
    std::cout << "Two numbers: "<< result_two << "\n";
    std::cout << "Three numbers: " << result_three << "\n";
}

#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <cmath>

typedef std::unordered_map<char, int> group_answers;

std::vector<group_answers> CreateVectorFromFile(std::string input_filename) {
    std::ifstream is(input_filename);
    std::string line;
    std::vector<group_answers> all;
    group_answers ga;
    while (std::getline(is, line)) {
        if (line == "") {
            all.push_back(ga);
            ga.clear();
            continue;
        }
        // For second part. Little bit hacky, but to keep track of number of persons in group
        ga['#'] += 1;  // Remove this line for part 1, mess up the results.
        for (char c: line) {
            ga[c] += 1;
        }
    }
    return all;
}

int SumYesCounts(const std::vector<group_answers>& yes_answers) {
    int yes = 0;
    for (const auto& ya: yes_answers)
        yes += ya.size();
    return yes;
}

int SumEveryoneYesCount(const std::vector<group_answers>& yes_answers) {
    int everyone_yes = 0;
    for (auto ya: yes_answers) {
        int passengers_in_group = ya['#'];
        for (const auto& answer: ya) {
            if (answer.first != '#' && answer.second == passengers_in_group)
                everyone_yes += 1;
        }
    }
    return everyone_yes;
}


int main() {
    std::unordered_map<char, int> group;
    auto yes_answers = CreateVectorFromFile("input.txt");
    std::cout << SumYesCounts(yes_answers) << "\n";
    std::cout << SumEveryoneYesCount(yes_answers) << "\n";

    return 0;
}

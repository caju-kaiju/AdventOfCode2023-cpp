// #include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

bool convert(std::string& line, const std::string& target, const std::string& replacement);
void convert_all(std::string& line, const std::string& target, const std::string& replacement);
void replace_spelled_digits(std::string& line);

int main() {
    std::ifstream file{"day1_input.txt"};
    if (!file) {
        std::cout << "Failed to open file";
        exit(1);
    }

    std::string line{""};
    std::optional<char> first;
    std::optional<char> last;
    unsigned int sum{0U};

    while (std::getline(file, line)) {
        replace_spelled_digits(line);

        for (auto const c : line) {
            // If we are not looking at a digit, skip to the next iteration
            if (!std::isdigit(c)) continue;

            if (!first) {
                first = c;
            } else {
                last = c;
            }
        }

        // If first is not set, then we have no numbers. Skip to the next iteration
        if (!first) continue;

        // If last is not set, then first and last are the same number
        if (!last) last = first.value();

        line = {first.value(), last.value()};
        sum += std::stoul(line);

        first.reset();
        last.reset();
    }

    std::cout << sum << std::endl;
    return 0;
}

bool convert(std::string& line, const std::string& target, const std::string& replacement) {
    size_t start_pos = line.find(target);
    if (start_pos == std::string::npos) return false;

    size_t last_pos = start_pos + target.size();

    // start_pos + 1 is to keep the first character of the match.
    // last_pos is to keep the last character of the match
    // This is done in case words link together and share letters
    // eightwothree -> e8t2ot3e
    std::string modified_line = line.substr(0, start_pos + 1) + replacement + line.substr(last_pos - 1);
    line = modified_line;
    return true;
}

void convert_all(std::string& line, const std::string& target, const std::string& replacement) {
    while (convert(line, target, replacement));
}

void replace_spelled_digits(std::string& line) {
    convert_all(line, "one", "1");
    convert_all(line, "two", "2");
    convert_all(line, "three", "3");
    convert_all(line, "four", "4");
    convert_all(line, "five", "5");
    convert_all(line, "six", "6");
    convert_all(line, "seven", "7");
    convert_all(line, "eight", "8");
    convert_all(line, "nine", "9");
}


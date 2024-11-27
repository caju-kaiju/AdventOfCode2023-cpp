#include <cctype>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

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

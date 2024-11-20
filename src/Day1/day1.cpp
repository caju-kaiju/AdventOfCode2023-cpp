#include <cctype>
#include <iostream>
#include <fstream>
#include <optional>

int main() {
    std::ifstream file{"day1_input.txt"};
    if (!file) {
        std::cout << "Failed to open file";
        exit(1);
    }

    std::string line{""};
    std::optional<char> first;
    std::optional<char> last;
    while (std::getline(file, line)) {
        for (unsigned int i = 0; i < line.size(); i++) {
            auto current_char = line.at(i);
            if (!std::isdigit(current_char)) continue;

            if (!first) {
                first = current_char;
            } else {
                last = current_char;
            }
        }

        if (first) std::cout << first.value() << " ";
        if (last) std::cout << last.value();
        std::cout << "\n";

        first.reset();
        last.reset();
    }




    return 0;
}

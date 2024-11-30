// #include <cctype>
// #include <cstddef>
// #include <sstream>
// #include <regex>
// #include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

class Number {
public:
    unsigned int num;
    unsigned int indices_start;
    unsigned int indices_end;

    Number() : num{0U}, indices_start{0U}, indices_end{0U} {}
    Number(unsigned int num, unsigned int indices_start, unsigned int indices_end)
        : num{num}, indices_start{indices_start}, indices_end{indices_end} {}
};

class Line {
public:
    std::vector<Number> numbers;

    Line() : numbers{0} {}
    Line(std::vector<Number> numbers) : numbers{numbers} {}
};

auto parse(const std::string& line) -> Line {
    std::vector<Number> numbers{0};

    std::string temp{""};
    std::optional<unsigned int> first;
    std::optional<unsigned int> last;

    // edge case: end of string
    for (unsigned int i = 0; i < line.size(); ++i) {
        if (std::isdigit(line.at(i))) {
            temp.append(line.at(i));

            if (!first) first = i else last = i;

            continue;
        }



    }

    // for (const auto& c : line) {
    //     if (!std::isdigit(c)) {
    //         if (0 < temp.size()) {
                
    //         }

    //         temp.clear();
    //     }



    }


    return Line{std::move(numbers)};
}

int main() {
    std::ifstream file{"day3_input_example.txt"};
    if (!file) {
        std::cout << "Failed to open file";
        exit(1);
    }

    std::vector<Line> lines{0};

    // Get all the games!
    std::string line{""};
    while (std::getline(file, line)) {
        lines.push_back(parse(line));
    }

    return 0;
}


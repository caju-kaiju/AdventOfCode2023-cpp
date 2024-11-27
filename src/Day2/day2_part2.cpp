#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>

std::regex regex_game_pattern{"Game (\\d+)"};
std::regex regex_red_pattern{"(\\d+) red"};
std::regex regex_green_pattern{"(\\d+) green"};
std::regex regex_blue_pattern{"(\\d+) blue"};

class Round {
public:
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    explicit Round(unsigned int red = 0U, unsigned int green = 0U, unsigned int blue = 0U)
    : red{red}, green{green}, blue{blue} {}

    std::string to_string() const {
        std::stringstream ss;
        ss << "red: " << this->red << ","
           << " green: " << this->green << ","
           << " blue: " << this->blue;

        return ss.str();
    }
};

class Game {
public:
    unsigned int id;
    std::vector<Round> rounds;

    explicit Game(unsigned int id, std::vector<Round> rounds)
    : id{id}, rounds{rounds} { }

    Round fold(const std::function<Round (const Round&, const Round&)>& func) const {
        Round result = this->rounds.at(0);

        for (auto it = this->rounds.begin() + 1; it != this->rounds.end(); ++it) {
            result = func(result, *it);
        }

        return result;
    }

    bool exists(const std::function<bool (Round)>& func) const {
        bool exists = false;

        for (const auto& round : this->rounds) {
            if (func(round)) {
                exists = true;
                break;
            }
        }

        return exists;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << "Game: " << this->id << " | ";

        for (const auto& round : this->rounds) {
            ss << round.to_string() << "; ";
        }

        return ss.str();
    }
};

Game parse(const std::string& line) {
    std::vector<std::string> tokens{};
    std::vector<Round> rounds{};

    // Create a copy of the string so that we can alter it. This is easier for parsing.
    // Add ";" to the end. Simple way to cover the edge case of the last token not ending in ';'.
    std::string scopy{line + ";"};

    // Parse out the games using ";"
    std::size_t pos = scopy.find(";");
    while (std::string::npos != pos) {
        tokens.emplace_back(scopy.substr(0, pos));
        scopy.erase(0, pos + 1);
        pos = scopy.find(";");
    }

    std::smatch match;

    // Pull out Game ID
    std::regex_search(tokens.at(0), match, regex_game_pattern);
    if (match.empty()) {
        std::cout << "No game id found.";
        exit(1);
    }
    unsigned int game_id = std::stoul(match[1].str());

    unsigned int red;
    unsigned int green;
    unsigned int blue;
    for (const auto& token : tokens) {
        red = 0;
        green = 0;
        blue = 0;

        std::regex_search(token, match, regex_red_pattern);
        if (!match.empty()) red = std::stoul(match[1].str());

        std::regex_search(token, match, regex_green_pattern);
        if (!match.empty()) green = std::stoul(match[1].str());

        std::regex_search(token, match, regex_blue_pattern);
        if (!match.empty()) blue = std::stoul(match[1].str());

        rounds.emplace_back(red, green, blue);
    }

    return Game{game_id, std::move(rounds)};
}

int main() {
    std::ifstream file{"day2_input.txt"};
    if (!file) {
        std::cout << "Failed to open file";
        exit(1);
    }

    std::vector<Game> games{};

    // Get all the games!
    std::string line{""};
    while (std::getline(file, line)) {
        games.push_back(parse(line));
    }

    // Setup the fold!
    auto fold = [](const Round& left, const Round& right) {
        unsigned int red = std::max(left.red, right.red);
        unsigned int green = std::max(left.green, right.green);
        unsigned int blue = std::max(left.blue, right.blue);

        return Round{red, green, blue};
    };

    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int power{0};
    Round fold_result;
    for (const auto& game : games) {
        fold_result = game.fold(fold);

        red = (fold_result.red <= 0) ? 1 : fold_result.red;
        green = (fold_result.red <= 0) ? 1 : fold_result.green;
        blue = (fold_result.red <= 0) ? 1 : fold_result.blue;

        power += red * green * blue;
    }

    std::cout << power;

    return 0;
}


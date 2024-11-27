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

    // Setup the filter!
    const unsigned int red_max = 12;
    const unsigned int green_max = 13;
    const unsigned int blue_max = 14;
    auto filter = [red_max, green_max, blue_max](const Round& round){
        if (round.red > red_max) { return true; };
        if (round.green > green_max) { return true; }
        if (round.blue > blue_max) { return true; }
        return false;
    };

    unsigned int sum{0};
    bool filter_result;
    for (const auto& game : games) {
        filter_result = game.exists(filter);

        if (!filter_result) {
            sum += game.id;
        }
    }

    std::cout << sum;

    return 0;
}


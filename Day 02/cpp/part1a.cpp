/**
--- Day 2: Cube Conundrum ---
https://adventofcode.com/2023/day/2

*/

#include <string>
#include <format>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <unordered_map>
#include <assert.h>

constexpr uint8_t RED_CUBES = 12;
constexpr uint8_t GREEN_CUBES = 13;
constexpr uint8_t BLUE_CUBES = 14;

enum class Color : uint8_t
{
    RED,
    GREEN,
    BLUE
};

struct GameInfo
{
    uint32_t id{0};
    std::unordered_map<Color, uint32_t> cubes;
};

Color get_color(const std::string &color)
{
    if (color == "red")
    {
        return Color::RED;
    }
    else if (color == "green")
    {
        return Color::GREEN;
    }
    else if (color == "blue")
    {
        return Color::BLUE;
    }
    else
    {
        std::cout << color << " not supported\n";
        std::abort();
    }
}

void process_cube(const std::string &cube, GameInfo &game)
{
    const auto separator = cube.find(" ");
    const Color color = get_color(cube.substr(separator + 1, cube.size() - separator));
    const uint32_t number = stoi(cube.substr(0, separator));
    game.cubes[color] = std::max(game.cubes[color], number);
}

void process_round(const std::string &round, GameInfo &game)
{
    std::size_t start{0};
    std::size_t end{0};
    while (end != std::string::npos)
    {
        end = round.find(',', start);
        const std::string cube = round.substr(start, (end - start));
        process_cube(cube, game);
        start = end + 2;
    }
}

GameInfo get_game_info(const std::string &line)
{
    GameInfo game{};
    std::size_t start{0};
    std::size_t end = line.find(':');
    game.id = stoi(line.substr(5, end));
    start = end + 2; // advance double colon and space
    while (end != std::string::npos)
    {
        end = line.find(';', start);
        const std::string round = line.substr(start, (end - start));
        process_round(round, game);
        start = end + 2; // advance semicolon and space
    }
    return game;
}

bool is_valid_game(GameInfo &game)
{
    return game.cubes[Color::RED] <= RED_CUBES && game.cubes[Color::GREEN] <= GREEN_CUBES && game.cubes[Color::BLUE] <= BLUE_CUBES;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream file("../input1.txt");
    int total{0};
    std::string line;
    while (std::getline(file, line))
    {
        GameInfo game = get_game_info(line);
        if (is_valid_game(game))
            total += game.id;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << std::format("The sum is: {}\n", total);
    std::cout << std::format("Execution time: {}\n", duration); //~110us
}
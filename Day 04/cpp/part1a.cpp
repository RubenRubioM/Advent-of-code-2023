/**
--- Day 4: Scratchcards ---
https://adventofcode.com/2023/day/4

*/

#include <string>
#include <format>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <utility>
#include <cmath>
#include <numeric>

std::vector<uint8_t> extract_numbers(const std::string numbers)
{
    std::vector<uint8_t> vector{};

    std::size_t start = numbers.find_first_not_of(' ');
    std::size_t end = numbers.find(' ', start);
    while (end != std::string::npos)
    {
        uint8_t number = stoi(numbers.substr(start, (end - start)));
        start = numbers.find_first_not_of(' ', end);
        end = numbers.find_first_of(' ', start);
        vector.push_back(number);
    }
    vector.push_back(stoi(numbers.substr(start, numbers.size())));
    return vector;
}
uint32_t get_total_prize(std::string &card)
{
    const std::size_t double_colon_position = card.find(':');
    const std::size_t separator_position = card.find('|');
    const auto my_numbers = extract_numbers(card.substr(double_colon_position + 2, (separator_position - 3) - double_colon_position));
    const auto winning_numbers = extract_numbers(card.substr(separator_position + 2, card.find('\n') - separator_position));
    const uint32_t occurrences = std::count_if(my_numbers.begin(), my_numbers.end(), [&winning_numbers](const auto my_number)
                                               { return std::find(winning_numbers.begin(), winning_numbers.end(), my_number) != winning_numbers.end(); });
    if (occurrences > 0)
    {
        return std::pow(2, occurrences - 1);
    }
    return 0;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream file("../input1.txt");
    uint32_t total{0};
    std::string line;
    while (getline(file, line))
    {
        total += get_total_prize(line);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << std::format("The sum is: {}\n", total);
    std::cout << std::format("Execution time: {}\n", duration); //~200us
}
/**
--- Day 1: Trebuchet?! ---
https://adventofcode.com/2023/day/1

*/

#include <string>
#include <vector>
#include <format>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>

uint8_t get_calibration_value(const std::string &calibration)
{
    char firstDigit{}, lastDigit{};
    for (auto &value : calibration)
    {
        if (isdigit(value))
        {
            if (!firstDigit)
            {
                firstDigit = value;
            }
            lastDigit = value;
        }
    }
    return stoi(std::string{firstDigit, lastDigit});
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream file("../input1.txt");
    int total{0};
    std::string line;
    while (std::getline(file, line))
    {
        total += get_calibration_value(line);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << std::format("The sum is: {}\n", total); 
    std::cout << std::format("Execution time: {}\n", duration); //~448us
}
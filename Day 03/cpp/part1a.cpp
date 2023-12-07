/**
--- Day 3: Gear Ratios ---
https://adventofcode.com/2023/day/3

*/

#include <string>
#include <format>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>
#include <utility>

uint32_t get_full_number_and_move(const std::string_view line, 
                                  std::size_t &position, 
                                  std::string& number)
{
    // Numbers are 3 digits max
    if (position == line.size())
        return stoi(number);

    ++position;
    while (isdigit(line[position]))
    {
        number.push_back(line[position]);
        ++position;
    }
    return stoi(number);
}

bool is_symbol(const char character)
{
    return (character != '.' && ispunct(character));
}

bool check_adjacent_symbols(const std::string_view previous, 
                            const std::string_view current, 
                            const std::string_view next, 
                            const std::size_t position)
{
    if (position > 0 && position < current.size())
    {
        // Not in the edges
        if (is_symbol(current[position - 1]) || is_symbol(current[position + 1])
            || (!previous.empty() 
                && (is_symbol(previous[position - 1]) 
                || is_symbol(previous[position]) 
                || is_symbol(previous[position + 1])))
            || (!next.empty() 
                && (is_symbol(next[position - 1]) 
                || is_symbol(next[position]) 
                || is_symbol(next[position + 1]))))
        {
            return true;
        }
    }
    if (position > 0 && position == current.size())
    {
        // In right edge
        if (is_symbol(current[position - 1])
            || (!previous.empty() 
                && (is_symbol(previous[position - 1])
                || is_symbol(previous[position])))
            || (!next.empty() 
                && (is_symbol(next[position - 1]) 
                || is_symbol(next[position]))))
        {
            return true;
        }
    }
    if (position == 0)
    {
        // In left edge
        if (is_symbol(current[position + 1]) 
            || (!previous.empty() 
                && (is_symbol(previous[position]) 
                || is_symbol(previous[position + 1])))
            || (!next.empty() 
                && (is_symbol(next[position]) 
                || is_symbol(next[position + 1]))))
        {
            return true;
        }
    }
    return false;
}

uint32_t get_line_total(const std::string_view previous, const std::string_view current, const std::string_view next)
{
    uint32_t total{0};
    std::string number{""};

    for (std::size_t position{0}; position < current.size(); ++position)
    {
        if (!isdigit(current[position]))
        {
            number.clear();
            continue;
        }
        else
        {
            number.push_back(current[position]);
        }
        if (check_adjacent_symbols(previous, current, next, position))
        {
            total += get_full_number_and_move(current, position, number);
            number.clear();
        }
    }
    return total;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream file("../input1.txt");
    uint32_t total{0};
    std::string previousLine, currentLine, nextLine;
    getline(file, currentLine);
    while (getline(file, nextLine))
    {
        total += get_line_total(previousLine, currentLine, nextLine);
        previousLine = currentLine;
        currentLine = nextLine;
    }
    total += get_line_total(previousLine, currentLine, nextLine);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << std::format("The sum is: {}\n", total);
    std::cout << std::format("Execution time: {}\n", duration); //~80us
}
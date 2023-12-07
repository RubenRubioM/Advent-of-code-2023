/**
--- Day 3: Gear Ratios ---
https://adventofcode.com/2023/day/3

*/
use std::fs::File;
use std::io::{self, BufRead};

fn is_symbol(character: char) -> bool {
    character != '.' && character.is_ascii_punctuation()
}

fn check_adjacent_symbols(previous: &str, current: &str, next: &str, position: usize) -> bool {
    let mut previous_chars = previous.chars();
    let mut current_chars = current.chars();
    let mut next_chars = next.chars();
    if position > 0 && position < current.len() {
        //Not in the edges
        if is_symbol(current_chars.nth(position - 1).unwrap())
            || is_symbol(current_chars.nth(position + 1).unwrap())
            || !previous.is_empty()
                && (is_symbol(previous_chars.nth(position - 1).unwrap())
                    || is_symbol(previous_chars.nth(position).unwrap())
                    || is_symbol(previous_chars.nth(position + 1).unwrap()))
            || !next.is_empty()
                && (is_symbol(next_chars.nth(position - 1).unwrap())
                    || is_symbol(next_chars.nth(position).unwrap())
                    || is_symbol(next_chars.nth(position + 1).unwrap()))
        {
            return true;
        }
    }
    if position > 0 && position == current.len() {
        // In right edge
        if is_symbol(current_chars.nth(position - 1).unwrap())
            || (!previous.is_empty()
                && (is_symbol(previous_chars.nth(position - 1).unwrap())
                    || is_symbol(previous_chars.nth(position).unwrap())))
            || (!next.is_empty()
                && (is_symbol(next_chars.nth(position - 1).unwrap())
                    || is_symbol(next_chars.nth(position).unwrap())))
        {
            return true;
        }
    }
    if position == 0 {
        // In left edge
        if is_symbol(current_chars.nth(position + 1).unwrap())
            || (!previous.is_empty()
                && (is_symbol(previous_chars.nth(position).unwrap())
                    || is_symbol(previous_chars.nth(position + 1).unwrap())))
            || (!next.is_empty()
                && (is_symbol(next_chars.nth(position).unwrap())
                    || is_symbol(next_chars.nth(position + 1).unwrap())))
        {
            return true;
        }
    }
    false
}

fn get_line_total(previous: &str, current: &str, next: &str) -> u32 {
    let mut total = 0;
    let mut number = String::new();

    for (position, current_char) in current.chars().enumerate() {
        if !current_char.is_digit(10) {
            number.clear();
            continue;
        } else {
            number.push(current_char);
        }

        if check_adjacent_symbols(previous, current, next, position) {
            // total += get_full_number_and_move(current, &mut position.clone(), &mut number);
            number.clear();
        }
    }

    total
}

fn main() -> io::Result<()> {
    let start_time = std::time::Instant::now();
    let file = File::open("../input1.txt")?;
    let reader = io::BufReader::new(file);
    let mut total = 0;
    let mut previous_line = String::new();
    let mut current_line = String::new();
    let mut next_line = String::new();

    for (i, line) in reader.lines().enumerate() {
        if i == 0 {
            current_line = line?;
            continue;
        }
        next_line = line?;
        total += get_line_total(&previous_line, &current_line, &next_line);
        previous_line = current_line.clone();
        current_line = next_line.clone();
    }
    next_line.clear();
    total += get_line_total(&previous_line, &current_line, &next_line);

    let end_time = std::time::Instant::now();
    let duration = end_time - start_time;

    println!("The sum is: {}", total);
    println!("Execution time: {:?}", duration);

    Ok(())
}

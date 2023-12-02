/*
--- Day 1: Trebuchet?! ---
https://adventofcode.com/2023/day/1

*/

use std::{
    fs::File,
    io::{self, BufRead},
};

fn get_calibration_value(calibration: String) -> u32 {
    let mut digits = calibration.chars().filter(char::is_ascii_digit);
    let first_digit: char = digits.next().unwrap_or('0');
    let second_digit: char = digits.last().unwrap_or(first_digit);
    format!("{first_digit}{second_digit}")
        .parse()
        .unwrap()
}

fn main() {
    let start_time = std::time::Instant::now();
    let file = File::open("../input1.txt").unwrap();
    let total: u32 = io::BufReader::new(file)
        .lines()
        .map_while(Result::ok)
        .map(get_calibration_value)
        .sum();

    let end_time = std::time::Instant::now();
    std::println!("The total sum is: {total}");
    std::println!("Execution time {:?}", (end_time - start_time)); // ~950us
}

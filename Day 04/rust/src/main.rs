/**
--- Day 4: Scratchcards ---
https://adventofcode.com/2023/day/4

*/
use std::{
    fs::File,
    io::{self, BufRead},
};

fn get_total_prize(card: String) -> u32 {
    let mut numbers_and_winners = card.split('|');
    let my_numbers: Vec<u8> = numbers_and_winners
        .next()
        .unwrap()
        .split(':')
        .last()
        .unwrap()
        .split_ascii_whitespace()
        .map(|number| number.trim().parse().unwrap())
        .collect();
    let winning_numbers: Vec<u8> = numbers_and_winners
        .next()
        .unwrap()
        .split_ascii_whitespace()
        .map(|number| number.trim().parse().unwrap())
        .collect();
    let occurrences = my_numbers.iter().filter(|number|{
        winning_numbers.iter().find(|value| value == number).is_some()
    }).count();

    if occurrences > 0 {
        2_u32.pow(occurrences as u32 - 1)
    } else {
        0
    }
    
}
fn main() {
    let start_time = std::time::Instant::now();
    let file = File::open("../input1.txt").unwrap();
    let total: u32 = io::BufReader::new(file)
        .lines()
        .map_while(Result::ok)
        .map(get_total_prize)
        .sum();

    let end_time = std::time::Instant::now();
    std::println!("The total sum is: {total}");
    std::println!("Execution time {:?}", (end_time - start_time)); // ~170us
}

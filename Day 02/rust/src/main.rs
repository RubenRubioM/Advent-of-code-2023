/**
--- Day 1: Cube Conundrum ---
https://adventofcode.com/2023/day/2

*/
use std::{
    fs::File,
    io::{self, BufRead},
};

const RED_CUBES: u32 = 12;
const GREEN_CUBES: u32 = 13;
const BLUE_CUBES: u32 = 14;

fn is_valid_cube(cube: &str) -> bool {
    let (number, color): (u32, &str) = (
        cube.split_whitespace()
            .next()
            .unwrap()
            .trim_start()
            .to_string()
            .parse()
            .unwrap(),
        cube.split_whitespace().last().unwrap(),
    );
    match color {
        "red" => {
            if number > RED_CUBES {
                return false;
            }
            true
        }
        "green" => {
            if number > GREEN_CUBES {
                return false;
            }
            true
        }
        "blue" => {
            if number > BLUE_CUBES {
                return false;
            }
            true
        }
        _ => {
            unreachable!();
        }
    }
}

fn is_valid_round(round: &str) -> bool {
    round.split(',').all(is_valid_cube)
}

fn valid_game_id(line: String) -> u32 {
    let mut splitted_line = line.split(':');
    let valid = splitted_line
        .clone()
        .last()
        .unwrap()
        .split(';')
        .all(is_valid_round);

    if valid {
        splitted_line
            .next()
            .unwrap()
            .split_whitespace()
            .last()
            .unwrap()
            .parse()
            .unwrap()
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
        .map(valid_game_id)
        .sum();

    let end_time = std::time::Instant::now();
    std::println!("The total sum is: {total}");
    std::println!("Execution time {:?}", (end_time - start_time)); // ~70us
}

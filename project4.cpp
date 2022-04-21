////////////////////////////////////
// ECE 150: Project 4
//
// Authors: Douglas Harder
//          Hiren Patel
////////////////////////////////////

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "project4.hpp"

namespace ece150 {
// File and string parsing
std::ifstream file{};
std::string content{};
std::istringstream input{};
std::string current_entry{};

// Ticker symbol.
std::string symbol{};

// Date fields.
unsigned int day{};
unsigned int month{};
unsigned int year{};

// Transaction type, shares and amount.
std::string buysell{};
unsigned int shares{};
double amount{};


////////////////////
// File functions //
////////////////////

// Open the file for reading
void open_file() {
  // If the file is already open, close it
  //  - this is just in case the file changed since the last opening
  if (file.is_open()) {
    file.close();
  }

  // Open the file and set the character position to zero
  file.open("transaction_history.txt");

  // If the file did not open, indicate an error occurred.
  if (!file.is_open()) {
    std::cerr << "[ERROR]: transaction_history.txt not found" << std::endl;
  }

  // Assign to the string the 'content' the contents of the file
  content = std::string(std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>());

  input.str(content);
}

void close_file() { file.close(); }

// Moves to the next transaction entry.
bool next_trans_entry() {
  std::getline(input, current_entry);
  std::stringstream ss(current_entry);
  ss.precision(2);

  if (!ss.str().empty()) {
    ss >> symbol >> day >> month >> year >> buysell >> shares >> amount;
    return true;
  } else {
    return false;
  }
}

// Functions to access the parsed fields.
std::string get_trans_symbol() { return symbol; }

unsigned int get_trans_day() { return day; }

unsigned int get_trans_month() { return month; }

unsigned int get_trans_year() { return year; }

unsigned int get_trans_shares() { return shares; }

double get_trans_amount() { return amount; }

bool get_trans_type() { return (buysell == "Buy") ? true : false; }

};  // namespace ece150

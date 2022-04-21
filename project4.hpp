#ifndef _PROJECT4_HPP_
#define _PROJECT4_HPP_
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

namespace ece150 {
// File and string parsing
extern std::ifstream file;
extern std::string content;
extern std::istringstream input;
extern std::string current_entry;

// Ticker symbol.
extern std::string symbol;

// Date fields.
extern unsigned int day;
extern unsigned int month;
extern unsigned int year;

// Transaction type, shares and amount.
extern std::string buysell;
extern unsigned int shares;
extern double amount;

////////////////////
// File functions //
////////////////////

// Open the file for reading
void open_file();

void close_file();

// Moves to the next transaction entry.
bool next_trans_entry();

// Functions to access the parsed fields.
std::string get_trans_symbol();

unsigned int get_trans_day();

unsigned int get_trans_month();

unsigned int get_trans_year();

unsigned int get_trans_shares();

double get_trans_amount();

bool get_trans_type();

};  // namespace ece150

#endif

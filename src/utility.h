#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <unordered_set>

enum Error_code { duplicate_error, not_present, success };

int string_to_int(const std::string& s);
std::string lower(std::string s);

#endif
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <stdexcept>

using namespace std;

enum Error_code { duplicate_error, not_present, success };

int string_to_int(const string& s);

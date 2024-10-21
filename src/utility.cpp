#include "utility.h"

int string_to_int(const string& s){
   istringstream instr(s);
   int n;
   instr >> n;
   return n;
}

std::string lower(std::string s)
{
    string result = "";

    for (char ch : s) result += tolower(ch);

    return result;
}

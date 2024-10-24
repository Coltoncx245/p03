#include "utility.h"

int string_to_int(const std::string& s){
   std::istringstream instr(s);
   int n;
   instr >> n;
   return n;
}

std::string lower(std::string s)
{
    std::string result = "";

    for (char ch : s) result += tolower(ch);

    return result;
}

#include "utility.h"

int string_to_int(const string& s){
   istringstream instr(s);
   int n;
   instr >> n;
   return n;
}

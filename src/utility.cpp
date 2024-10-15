#include "utility.h"

int string_to_int(string s){
   istringstream instr(s);
   int n;
   instr >> n;
   return n;
}
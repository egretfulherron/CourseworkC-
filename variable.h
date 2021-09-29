#pragma once
#include <string>
using namespace std;

//struct to store the variables in 
struct variable {
  string name;
  int line;
  string type;
  int function_count;
  int usage;
};
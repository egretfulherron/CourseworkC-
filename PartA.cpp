//Author: Emily Herron
//main for data sort
#include <cstring>
#include <iostream>
#include <string>
#include <regex>
#include<fstream>
#include<vector>
#include<sstream>
#include"BST.hpp"
#include"variable.h"
using namespace std;
//variables
BST word_tree;
string line;
int other_variable_counter = 0;
int z;
int long_flag = 0;
int for_counter = 0;
int if_counter = 0;
int while_counter = 0;
int array_flag = 0;
int skip_flag = 0;
int function_counter = 0;
int line_counter = 0;
int prim_flag = 0;
string token;
int name_flag = 0;


int main(int argc, char const *argv[]) {

   struct variable new_variable; 
   struct variable another_new_variable;
   vector <variable> symbol_table; // to store variables
   tree_node *root = new tree_node; // new root 
   ifstream input; // test file
   string filename = argv[1]; // read from command line
   input.open(filename);

   while (getline(input, line)) {
       // until the end of the file, each line
      line_counter++;
      stringstream stream(line); 
      while (stream >> token) {
           // until the end of the line, each token
         if (symbol_table.size() != 0) {

            if (prim_flag == 0 && name_flag == 0) {
                //if there is no primitive types or function, check if the token if one of the variables already in the table
               for (int l = 0; l <= symbol_table.size(); l++) {

                  if (token == symbol_table[l].name){
                      // if it is, and if the type and function count is the same
                     if (symbol_table[l].type == "variable" && function_counter == symbol_table[l].function_count) {

                        symbol_table[l].usage++; // increment the usage

                     } else if (symbol_table[l].type == "function") {  

                        symbol_table[l].usage++; // increment the usage 
                     }
                     }
                  }
               }
            }
         
         
         if (name_flag == 1) { // the name flag is switched on, following the word which sets the prim flag
           
            if (token == ";" || token == "=" || token == "," || token == ")") {  // to ensure variables and functions with the same name are classified differently

               new_variable.type = "variable"; //this sets the type

            } else if (array_flag == 1) {

               new_variable.type = "array";

            } else { 

               new_variable.type = "function";

               function_counter++; //if not an array and not a variable, it must be a function

            }

            name_flag = 0;
            symbol_table.push_back(new_variable); // add to symbol_table
         }

         if (prim_flag == 1) { // prim flag comes on when a primitive type is found, so this is the token with the variable name

            if (token != "long") { 
               name_flag = 1; // so we know we are still on the word after prim
               new_variable.name = token;  // sets the variable properties
               new_variable.line = line_counter;
               new_variable.function_count = function_counter;
               new_variable.usage = 0;
               prim_flag = 0; // turns flag off
            }
         }
         if (token == "int" || token == "float" || token == "short" || token == "double" || token == "char" || token == "int*" || token == "float*" || token == "short*" || token == "double*" || token == "char*" || token == "long" || token == "long*") {
            prim_flag = 1; // demonstably a primitive syntax byte will set flag to adhere
            other_variable_counter++; // for partA counting

         } else if (token == "long") { // flag system for long is in place to prevent the double counting on 'long long' types
            other_variable_counter++;
            prim_flag = 1;
            long_flag = 1;

         } else if (token == "if") { // self-explanatory
            if_counter++;

         } else if (token == "for") {  // self-explanatory
            for_counter++;

         } else if (token == "while") {  // self-explanatory
            while_counter++;
         } else if (token == "array") {  // self-explanatory
            array_flag = 1;
         }
      }
   }

   ofstream table_output;
   table_output.open("identifiers.txt"); //opens file
   ofstream tree_output;
   tree_output.open("tree.txt"); //opens file
   cout << "In this file there were:" << endl; // prints part A to console  
   cout << for_counter << " for loop(s), " << endl;
   cout << while_counter << " while loop(s), " << endl;
   cout << if_counter << " if statement(s), " << endl;
   cout << other_variable_counter << " variables," << endl;
   cout << function_counter << " function(s)." << endl;

      for (int z = 0; z < symbol_table.size(); z++) { // prints symbol_table to identifiers.txt

         table_output << symbol_table[z].name << ",    " << symbol_table[z].line << ",   " << symbol_table[z].type << ",    " << symbol_table[z].usage << endl;
         table_output << endl;
         word_tree.update(symbol_table[z]);
      }
   word_tree.print_tree_table(tree_output); //prints BST to tree.txt
   word_tree.timber(); //deletes tree
   
   table_output.close();
   tree_output.close();

   return 0;
}
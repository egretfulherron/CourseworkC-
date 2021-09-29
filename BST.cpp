//Author: Emily Herron
//binary search tree class

#include "BST.hpp"
#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

// private method to destroy tree 
void BST::DestroyBranches(tree_node *root) { 
   if (root) {
      DestroyBranches(root -> left);
      DestroyBranches(root -> right);
      delete root;
   }
}

bool BST::search(variable d) { //is called by private update to see if the variable is already in the tree, seaarches recursively
   tree_node *temp = root;
   while (temp != NULL) {
        if (temp -> variable_inside_struct.name == d.name && temp -> variable_inside_struct.function_count == d.function_count) {
            return true;
        } else {
            if (d.name > temp -> variable_inside_struct.name) {
                temp = temp -> right;
            } else {
                temp = temp -> left;
            }
        }
   }
   return false;
}

// is used to add new node into tree
void BST::update_helper(tree_node **root, variable &new_variable) { 

   if (!search(new_variable)) { // if the variable isnt there
      if ( *root == nullptr) {
         *root = new tree_node(); // either add it to the empty tree
         ( *root) -> variable_inside_struct = new_variable;
         ( *root) -> left = nullptr;
         ( *root) -> right = nullptr;
         ( *root) -> counter = new_variable.usage;
      } else {
            if (new_variable.name < ( *root) -> variable_inside_struct.name) { // or compare it to the current 'root' and see if it is smaller (alphabetically before) or bigger, and then follow down 
            update_helper( & (( *root) -> left), new_variable); // calls recursively to ensure that it goes to the correct place
            } else {
            update_helper( & (( *root) -> right), new_variable);
            }
      }
    } 
    else if (search(new_variable)){  // if it's already in , increment counter
       if ( *root == nullptr) {
      return;
   } else if (new_variable.name == ( *root) -> variable_inside_struct.name) {
      ( *root) -> counter++;
   }
   else if (new_variable.name < ( *root) -> variable_inside_struct.name) {
      update_helper(& (( *root) -> left), new_variable);
   } else {
      update_helper( & (( *root) -> right), new_variable);
   }
    }
   
}
 //prints the tree to a file
string BST::print_tree_table_helper(ofstream & outputFile, tree_node *root) { 
  
   if (root == NULL) {
      return "";
   }
   print_tree_table_helper(outputFile, root -> left);
   outputFile << root -> variable_inside_struct.name << ",    " << root -> variable_inside_struct.line << ",    " << root -> variable_inside_struct.type << ",    " << root -> counter << endl;
   outputFile << " " << endl; // nice and clean
   print_tree_table_helper(outputFile, root -> right); //prints in the symbol table styble
   return "";
}
//public methods

 void BST::timber() { //public method to destroy tree 
   DestroyBranches(root);
}
//Creates an empty tree
BST::BST() {
   root = nullptr;
}

// public update calls private update to update tree
void BST::update( variable &new_variable) { 
   update_helper( & root, new_variable);
}

 // public print calls private print to print
string BST::print_tree_table(ofstream & outputFile) {
   print_tree_table_helper(outputFile, root); 
   return "";
}
//Author: Emily Herron
//binary search tree library
#pragma once
#include "variable.h"

using namespace std;
//One node of the BST (Binary Search Tree)
struct tree_node {
   variable variable_inside_struct;
   tree_node *left;
   tree_node *right;
   int counter;
};

class BST {
   public:
       variable *new_variable;
        BST(); //Creates an empty tree
        void timber(); //Destructor
        void update(variable &new_variable); //updates tree with new variable/node
        string print_tree_table(ofstream & outputFile); //Returns a string representation of the tree

   private:
        tree_node *root; //The root node of the tree
        void update_helper(tree_node **root, variable &new_variable); //private insert helper
        bool search(variable d); // returns true if the node is already in the tree
        void DestroyBranches(tree_node *root); //Destructor
        string print_tree_table_helper(ofstream & outputFile, tree_node * root); //private print tree helper
};
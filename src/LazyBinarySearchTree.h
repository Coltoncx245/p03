#ifndef LBST_H
#define LBST_H

#include "utility.h"
#include "TreeNode.h"
using std::string;


class LazyBinarySearchTree
{
private:
    int count{};
    TreeNode<int>* root;

public:
    LazyBinarySearchTree() : root(nullptr), count(0) {}

    bool insert(int data);
    bool remove(int data);
    int findMin();
    int findMax();
    bool contains(int target);
    string print();
    int height();
    int size();


    
    std::unordered_set<string> Commands{
    "insert",
    "remove",
    "findmin",
    "findmax",
    "contains",
    "print",
    "height",
    "size"
    };


protected:
    void recursive_preorder(TreeNode<int>* node, string &result);
    bool search_and_insert(TreeNode<int>* &sub_root, int new_data);
    bool search_and_delete(TreeNode<int>* &sub_root, int target);
    virtual void lazy_print(TreeNode<int>* node, string &result);
    int recursive_height(TreeNode<int>* node);
    int recursive_size(TreeNode<int>* node);

};


/* @brief TreeException (Extends std::exception)
*  
*  Class containing exception methods for LazyBinarySearchTree
*/
class TreeException : public std::exception
{
private: 
    string message;
    string command;
    string arg;

public:
    TreeException(const char* msg, const char* command, const int arg)
    {
        this->message = msg;
        this->command = command;
        this->arg = std::to_string(arg);
    }


    const char* what()
    {
        return (this->message + " | Command: " + this->command + " | Argument: " + this->arg).c_str();
    }

};

void process_command(std::string &command, std::string &arg, LazyBinarySearchTree &tree, std::ofstream &outfile);
void process_command(std::string &command, LazyBinarySearchTree &tree, std::ofstream &outfile);


#endif
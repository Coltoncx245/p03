#include "utility.h"
#include "TreeNode.h"

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
    std::string print();
    int height();
    int size();
    
    std::unordered_set<std::string> Commands{
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
    void recursive_preorder(TreeNode<int>* node, std::string &result);
    bool search_and_insert(TreeNode<int>* &sub_root, int new_data);
    bool search_and_delete(TreeNode<int>* &sub_root, int target);
    virtual void lazy_print(TreeNode<int>* node, std::string &result);
    int recursive_height(TreeNode<int>* node);
    int recursive_size(TreeNode<int>* node);

};

class TreeException : public std::exception
{
private: 
    std::string message;
    std::string command;
    std::string arg;

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

// INSERT IMPLEMENTATION
bool LazyBinarySearchTree::insert(int data)
{
    if (data < 1 || data > 99) {throw TreeException("Error: illegal argument (not in range)", "insert", data); }

    if (this->root == nullptr)
    { // Create a new node with the key
        this->root = new TreeNode<int>(data);
        ++count;
        return true; // New record inserted
    }
    else { return search_and_insert(this->root, data); }  // Use search_and_insert to handle recursion
}

void LazyBinarySearchTree::recursive_preorder(TreeNode<int>* node, std::string &result)
{
    if (node != nullptr)
    {
        lazy_print(node, result);  // Visit the node and accumulate its key into the result string
        recursive_preorder(node->left, result);  // Traverse left subtree
        recursive_preorder(node->right, result);  // Traverse right subtree
    }
}

bool LazyBinarySearchTree::search_and_insert(TreeNode<int>* &sub_root, int new_data)
{
    if (sub_root == nullptr)
    { // Insert new node here
        sub_root = new TreeNode<int>(new_data);
        ++count;
        return true; // New element inserted
    }
    else if (new_data < sub_root->key) { return search_and_insert(sub_root->left, new_data); } // Traverse left subtree
    else if (new_data > sub_root->key) { return search_and_insert(sub_root->right, new_data); } // Traverse right subtree
    else if (sub_root->deleted)
    { // If the node is marked as deleted, "undelete" it
        sub_root->deleted = false;
        return true;  // Element "undeleted"
    }
    else { return false; } // Data already exists and is not marked as deleted. No new insertion
}

// REMOVE IMPLEMENTATION
bool LazyBinarySearchTree::remove(int dataToDelete) { return search_and_delete(this->root, dataToDelete); }

bool LazyBinarySearchTree::search_and_delete(TreeNode<int>* &sub_root, int target)
{
    if (sub_root == nullptr) { return false; }
    if (sub_root->key == target) { return sub_root->deleted = true; }
    else if (target < sub_root->key) { return search_and_delete(sub_root->left, target); }
    else if (target > sub_root->key) { return search_and_delete(sub_root->right, target); }
    return false;
}

// FIND MIN IMPLEMENTATION
int LazyBinarySearchTree::findMin()
{
    if (this->root == nullptr) { return -1; } // Return a sentinel value or throw an exception as needed

    std::stack<TreeNode<int>*> stack;  // Store pointers to nodes, not ints
    TreeNode<int>* r = this->root;

    while (r) // Traverse left leg of the tree, pushing all nodes onto stack
    {
        stack.push(r);
        r = r->left;
    }

    // Now, stack has all elements in the left leg of the tree
    while (!stack.empty())
    {
        TreeNode<int>* node = stack.top();
        if (!node->deleted) { return node->key; } // Return the first undeleted node's key
        stack.pop();
    }

    return -1;  // If no valid (undeleted) node is found
}

// FIND MAX IMPLEMENTATION
int LazyBinarySearchTree::findMax()
{
    if (this->root == nullptr) { return -1; } // Return a sentinel value or throw an exception as needed

    std::stack<TreeNode<int>*> stack;  // Store pointers to nodes, not ints
    TreeNode<int>* r = this->root;

    // Traverse right leg of the tree, pushing all nodes onto stack
    while (r)
    {
        stack.push(r);
        r = r->right;
    }

    // Now, stack has all elements in the right leg of the tree
    while (!stack.empty())
    {
        TreeNode<int>* node = stack.top();
        stack.pop();

        if (!node->deleted) { return node->key; } // Return the first undeleted node's key
    }

    return -1;  // If no valid (undeleted) node is found
}

// CONTAINS IMPLEMENTATION
bool LazyBinarySearchTree::contains(int target)
{
    TreeNode<int>* node = this->root;
    while (node != nullptr)
    {
        if (node->key == target) { return !node->deleted; }
        else if (target < node->key) { node = node->left; }
        else { node = node->right; }
    }
    return false;
}

// PRINT IMPLEMENTATION
std::string LazyBinarySearchTree::print()
{
    std::string result;
    if (this->root == nullptr) { result = "EMPTY TREE"; }
    else { recursive_preorder(this->root, result); }
    return result;
}

// LAZY PRINT FUNCTION
void LazyBinarySearchTree::lazy_print(TreeNode<int>* node, std::string &result)
{
    if (node->deleted) { result += "*"; }
    result += std::to_string(node->key) + " ";
}


int LazyBinarySearchTree::height()
{
    if (root == nullptr) throw std::out_of_range("Empty Tree");
    else return recursive_height(root)-1;
}

int LazyBinarySearchTree::recursive_height(TreeNode<int>* node)
{
    if (node == nullptr) return 0;
    else if (node->left == nullptr && node->right == nullptr) return 1;
    else
    {
        int left_subtree = recursive_height(node->left);
        int right_subtree = recursive_height(node->right);
        return left_subtree > right_subtree ? left_subtree+1 : right_subtree+1;
    }
}


int LazyBinarySearchTree::size()
{
    if (root == nullptr) throw std::out_of_range("Empty Tree");
    else return recursive_size(root);
}

int LazyBinarySearchTree::recursive_size(TreeNode<int>* node)
{
    if (node == nullptr) return 0;
    else return recursive_size(node->left) + recursive_size(node->right) + 1;
}

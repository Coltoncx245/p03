#include "utility.h"
#include "TreeNode.h"


class LazyBinarySearchTree
{
private:
    int count{};
    TreeNode<int>* root;  // Use int instead of Record

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

protected:
    void recursive_preorder(TreeNode<int>* node, std::string &result);
    bool search_and_insert(TreeNode<int>* &sub_root, int new_data);
    bool search_and_delete(TreeNode<int>* &sub_root, int target);
    virtual void lazy_print(TreeNode<int>* node, std::string &result);

};

// INSERT IMPLEMENTATION
bool LazyBinarySearchTree::insert(int data)
{
    if (data < 1 || data > 99) { throw std::out_of_range("Data must be in the range [1,99]."); }

    if (this->root == nullptr)
    { // Create a new node with the data
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
        lazy_print(node, result);  // Visit the node and accumulate its data into the result string
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
    else if (new_data < sub_root->data) { return search_and_insert(sub_root->left, new_data); } // Traverse left subtree
    else if (new_data > sub_root->data) { return search_and_insert(sub_root->right, new_data); } // Traverse right subtree
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
    if (sub_root->data == target) { return sub_root->deleted = true; }
    else if (target < sub_root->data) { return search_and_delete(sub_root->left, target); }
    else if (target > sub_root->data) { return search_and_delete(sub_root->right, target); }
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
        stack.pop();

        if (!node->deleted) { return node->data; } // Return the first undeleted node's data
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

        if (!node->deleted) { return node->data; } // Return the first undeleted node's data
    }

    return -1;  // If no valid (undeleted) node is found
}

// CONTAINS IMPLEMENTATION
bool LazyBinarySearchTree::contains(int target)
{
    TreeNode<int>* node = this->root;
    while (node != nullptr)
    {
        if (node->data == target) { return !node->deleted; }
        else if (target < node->data) { node = node->left; }
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
    result += std::to_string(node->data) + " ";
}

// HEIGHT and SIZE IMPLEMENTATIONS (Placeholders)
int LazyBinarySearchTree::height()
{
    // Implementation for height logic using pre-order traversal
    return 0;
}

int LazyBinarySearchTree::size() { /*return count;*/ }

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

    static void process_command(std::string &command, std::string &arg, LazyBinarySearchTree &tree, std::ofstream &outfile);
    static void process_command(std::string &command, LazyBinarySearchTree &tree, std::ofstream &outfile);
    
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




/*
* @brief Inserts data into the tree
* 
* Wrapper function for recursive search_and_insert() to insert data in the tree. If the data already exists in the tree but is flagged
* as deleted, it is simply unflagged.
* @param data: Integer between 1 and 99
* @return True when data is succesfully inserted, false if data already exists in tree and is not marked as deleted
*
*/
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

/*@brief Recursively traverses tree and inserts data as a new leaf node
* 
* Creates a new TreeNode if data does not already exist in the tree
* @param sub_root: The root of the sub-tree to be traversed
* @param new_data: Integer data to be inserted
* @return True True when data is succesfully inserted, false if data already exists in tree and is not marked as deleted
*/
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

/*@brief Returns a string with tree node data using preorder traversal
*
* Wrapper function for recursive_preorder(), which traverses the tree and appends node data to the string param
* @return string containing tree data
*/
string LazyBinarySearchTree::print()
{
    string result;
    if (this->root == nullptr) { result = "EMPTY TREE"; }
    else { recursive_preorder(this->root, result); }
    return result;
}

/*@brief Traverses the tree in recursive_preorder (VLR). Used exclusively for print().
*
* @param node: TreeNode to be used as root of subtree for traversal
* @param result: String appended with tree data during traversal
*/
void LazyBinarySearchTree::recursive_preorder(TreeNode<int>* node, string &result)
{
    if (node != nullptr)
    {
        lazy_print(node, result);  // Visit the node and accumulate its key into the result string
        recursive_preorder(node->left, result);  // Traverse left subtree
        recursive_preorder(node->right, result);  // Traverse right subtree
    }
}

/*@brief Appends node data to string result using specified convention (* == deleted node)
* @param node: Tree node whose data will be appended to string
* @param result: String appended to with node data, passed by reference
*/
void LazyBinarySearchTree::lazy_print(TreeNode<int>* node, string &result)
{
    if (node->deleted) { result += "*"; }
    result += std::to_string(node->key) + " ";
}

/*@brief Marks data in the tree as deleted, making it unavailable
*
* Wrapper for recursive function search_and_delete(). 
* @warning  Does not actually delete the node, but flags it as deleted
* @param dataToDelete: integer data to be removed from the tree.
*/
bool LazyBinarySearchTree::remove(int dataToDelete) { return search_and_delete(this->root, dataToDelete); }

/*@brief Recursively traverses the tree until target data is found, then marks that node as deleted
* @param sub_root: TreeNode used as root of subtree to be traversed
* @param target: Target data to be removed from the tree. 
* @return True if target is found and marked as deleted. False if target is not found in the tree.
*/
bool LazyBinarySearchTree::search_and_delete(TreeNode<int>* &sub_root, int target)
{
    if (sub_root == nullptr) { return false; }
    if (sub_root->key == target) { return sub_root->deleted = true; }
    else if (target < sub_root->key) { return search_and_delete(sub_root->left, target); }
    else if (target > sub_root->key) { return search_and_delete(sub_root->right, target); }
    return false;
}

/* @brief Returns the smallest non-deleted value in the tree
* 
* Traverses the leftmost branch of the tree, storing all of the nodes on a stack. Once the deepest leftmost node is reached, 
* nodes marked "deleted" are popped from the stack until the first non-deleted node is reached.   
* 
* @return int, smallest integer value stored in the tree, -1 if tree is empty or all nodes are deleted
*/
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


/* @brief Returns the largest non-deleted value in the tree
* 
* Traverses the rightmost branch of the tree, storing all of the nodes on a stack. Once the deepest rightmost node is reached, 
* nodes marked "deleted" are popped from the stack until the first non-deleted node is reached.   
* 
* @return int, largest integer value stored in the tree, -1 if tree is empty or all nodes are deleted
*/
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

/* @brief checks if the target value is both in the tree and non-deleted
* @param target: integer target to be searched for
* @return True if target is in tree and not flagged as deleted, False if target not in tree or flagged as deleted 
*/
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


/* @brief Returns the height of the tree (number of edges in the longest branch)
*
*  Wraps recursive_height()
*/
int LazyBinarySearchTree::height()
{
    if (root == nullptr) throw std::out_of_range("Empty Tree");
    else return recursive_height(root)-1;
}

/* @brief Recursively traverses the left and right subtrees of the node parameter, returning the height of the larger of the two.
*  @param TreeNode: to be used as root of subtree for traversal
* @return int number of edges in longest branch of tree
*/
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

/*@brief Returns the number of nodes in the tree, including nodes marked deleted
* 
* Wraps recursive_size()
*/
int LazyBinarySearchTree::size()
{
    if (root == nullptr) throw std::out_of_range("Empty Tree");
    else return recursive_size(root);
}

/*@brief Recursively traverses tree, adding one for each node (including those marked deleted.)
* @param node: TreeNode to be used as root of subtree for traversal
*/
int LazyBinarySearchTree::recursive_size(TreeNode<int>* node)
{
    if (node == nullptr) return 0;
    else return recursive_size(node->left) + recursive_size(node->right) + 1;
}



// Process commands which take no argument
void process_command(std::string &command, LazyBinarySearchTree &tree, std::ofstream &outfile)
{
   command = lower(command);
   if (tree.Commands.count(command))
   {
      if (command == "print"){outfile << tree.print() << std::endl;}
      else if (command == "height"){outfile << tree.height() << std::endl;}
      else if (command == "findmax"){outfile << tree.findMax() << std::endl;}
      else if (command == "findmin"){outfile << tree.findMin() << std::endl;}
      else if (command == "size"){outfile << tree.size() << std::endl;}
      else if (command == "insert" || command == "remove" || command == "contains")
      {
         throw TreeException("Error: Command expects key, but none found", command.c_str(), -1);
      }
   }
   else{throw TreeException("Error: Invalid command", command.c_str(), -1);}
}

// Process commands which take an argument
void process_command(std::string &command, std::string &arg, LazyBinarySearchTree &tree, std::ofstream &outfile)
{
   command = lower(command);
   arg = lower(arg);
   if (tree.Commands.count(command))
   {
      if (command == "insert"){outfile << (tree.insert(string_to_int(arg)) ? "true" : "false") << std::endl;}
      else if (command == "remove"){outfile << (tree.remove(string_to_int(arg)) ? "true" : "false") << std::endl;}
      else if (command == "contains"){outfile << (tree.contains(string_to_int(arg)) ? "true" : "false") << std::endl;}
   }
   else{outfile << "Error: " << command << " (invalid command)" << std::endl;}
}

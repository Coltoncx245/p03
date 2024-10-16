#include "utility.h"
#include "Binary_node.h"
#include "Search_tree.h"

template <class Record>
class Lazy_tree: public Search_tree<Record>
{
private:
    int count{};

public:
    bool insert(const Record &data);
    bool remove(const Record &data);
    int findMin();
    int findMax();
    bool constains(Binary_node<Record>* &sub_root, const Record &target);
    std::string print();
    int height();
    int size();


protected:
    bool search_and_insert(Binary_node<Record>* &sub_root, const Record &new_data);
    bool search_and_delete(Binary_node<Record>* &sub_root, const Record &target);
    Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, const Record &target) const;
    virtual void lazy_print(Binary_node<Record>* node, std::string &result) = 0;

};

// INSERT IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::insert(const Record &data)
{
    if (data < 1 || data > 99){throw std::out_of_range("Data must be in the range [1,99].");}

    if (this->root == nullptr)
    {
        // Create a new node with the data
        this->root = new Binary_node<Record>(data);
        ++count;
        return true; // New records inserted
    }
    else{return search_and_insert(this->root, data);} // Use search_and_insert to handle recursion
}

template <class Record>
bool Lazy_tree<Record>::search_and_insert(Binary_node<Record>* &sub_root, 
                                          const Record &new_data)
{
    if (sub_root == nullptr)
    {
        // Insert new node here
        sub_root = new Binary_node<Record>(new_data);
        ++count;
        return true; // New element inserted
    }
    else if (new_data < sub_root->data){return search_and_insert(sub_root->left, new_data);} // Traverse left subtree
    else if (new_data > sub_root->data){return search_and_insert(sub_root->right, new_data);} // Traverse right subtree
    else if (sub_root->deleted)
    {
        // If the node is marked as deleted, "undelete" it
        sub_root->deleted = false;
        return true;  // Element "undeleted"
    }
    else{return false;} // Data already exists and is not marked as deleted. No new insertion
}

//REMOVE IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::remove(const Record &dataToDelete)
{
    return search_and_delete(this->root, dataToDelete);
}

// RECURSIVE REMOVE
template <class Record>
bool Lazy_tree<Record>::search_and_delete(Binary_node<Record>* &sub_root, 
                                          const Record &target)
{
    if (sub_root == NULL){return 0;}
    if (sub_root->data == target){return sub_root->deleted = 1;}
    else if (target < sub_root->data){return search_and_delete(sub_root->left, target);}
    else if (target > sub_root->data){return search_and_delete(sub_root->right, target);}
}


// FIND MIN IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::findMin()
{
    if (this->root == nullptr){return -1;}
    
    std::stack<Record> stack;
    Binary_node<Record>* r = this->root;
    // traverse left leg of tree, pushing all nodes onto stack
    while (r)                   
    {
        stack.push(r->data);    
        r = r->left;        
    }
    // stack now has all elements in left leg of tree in descending order (from top down)
    while (stack.top().deleted){stack.pop();} // remove deleted elements from the top of the stack
    return stack.top();                       
}

// FIND MAX IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::findMax()
{
    if (this->root == nullptr){return -1;}
    
    std::stack<Record> stack;
    Binary_node<Record>* r = this->root;
    // traverse RIGHT leg of tree, pushing all nodes onto stack
    while (r)                   
    {
        stack.push(r->data);    
        r = r->right;        
    }
    // stack now has all elements in left leg of tree in descending order (from top down)
    while (stack.top().deleted){stack.pop();} // remove deleted elements from the top of the stack
    return stack.top();   
}

// CONSTAINS IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::constains(const Record &target)
{
    if (sub_root == NULL){return false;}
    if (sub_root->data == target){return !target->deleted;}
    else if (target < sub_root->data){return constains(sub_root->left, target);}
    else if (target > sub_root->data){return constains(sub_root->right, target);}
}

// PRINT IMPLEMENTATION
template <class Record>
std::string Lazy_tree<Record>::print()
{
    std::string result;
    if (this->root == nullptr) result = "EMPTY TREE";
    else result = recursive_preorder(this->root, &Lazy_tree<Record>::lazy_print); // Perform a pre-order traversal and build the result string

    return result;
}

// LAZY PRINT FUNCTION
template <class Record>
void Lazy_tree<Record>::lazy_print(Binary_node<Record>* node, 
                                   std::string &result)
{
    if (node->deleted) result += "*";  // Mark deleted nodes with an asterisk before the data
    result += std::to_string(node->data) + " ";  // Add the node's data followed by a space
}

// HEIGHT IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::height()
{

}

// SIZE IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::size()
{

}

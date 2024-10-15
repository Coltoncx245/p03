#include "utility.h"
#include "Binary_node.h"

template <class Record>
class Lazy_tree: public Search_tree<Record>
{
public:
    bool insert(const Record &data);
    bool remove(const Record &data);
    int findMin();
    int findMax();
    bool constains(const Record &data);
    std::string print();
    int height();
    int size();


protected:
    bool search_and_insert(Binary_node<Record>* &sub_root, const Record &new_data);
    bool search_and_delete(Binary_node<Record>* &sub_root, const Record &target);
    Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, const Record &target) const;

};

// INSERT IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::insert(const Record &data)
{
    if (this->root == nullptr)
    {
        // Create a new node with the data
        this->root = new Binary_node<Record>();
        ++count;
        return true;
    }
    else
    {
        // Use search and insert to handle recursion
        return false;
    }
}

//REMOVE IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::remove(const Record &data)
{

}

// RECURSIVE REMOVE
template <class Record>
bool Lazy_tree<Record>::search_and_delete(Binary_node<Record>* &sub_root, const Record &target)
{

}


// FIND MIN IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::findMin()
{

}

// FIND MAX IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::findMax()
{

}

// CONSTAINS IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::constains(const Record &data)
{


}

// PRINT IMPLEMENTATION
template <class Record>
std::string Lazy_tree<Record>::print()
{

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

template <class Record>
bool Lazy_tree<Record>::search_and_insert(Binary_node <Record>* &sub_root, const Record &new_data)
{
    if (sub_root == nullptr)
    {
        sub_root = new Binary_node<Record>(new_data);
        ++ count;
        return true;
    }
    else if (new_data < sub_root->data)
    {
        return search_and_insert(sub_root->left, new_data);
    }
    else if (sub_root->deleted)
    {
        // If the node is marked as deleted, we undelete it
        sub_root->deleted = false;
        return true;
    }
    else return false; // Data already exists and is not marked as deleted
}

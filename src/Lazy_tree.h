#include "utility.h"
#include "Binary_node.h"

template <class Record>
class Lazy_tree: public Search_tree<Record>
{
public:
    bool insert(const Record &data);
    bool remove(const Record &data);
    int findMin();
    int Lazy_tree<Record>::recursiveMin(Binary_node<Record>* sub_root);
    int findMax();
    int Lazy_tree<Record>::recursiveMax(Binary_node<Record>* sub_root);
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

}

//REMOVE IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::remove(const Record &dataToDelete)
{
    return search_and_delete(this->root, dataToDelete);
}

// RECURSIVE REMOVE
template <class Record>
bool Lazy_tree<Record>::search_and_delete(Binary_node<Record>* &sub_root, const Record &target)
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
}

template <class Record>
int Lazy_tree<Record>::recursiveMin(Binary_node<Record>* sub_root)
{
    
}

// FIND MAX IMPLEMENTATION
template <class Record>
int Lazy_tree<Record>::findMax()
{

}

// CONSTAINS IMPLEMENTATION
template <class Record>
bool Lazy_tree<Record>::constains(const Record &target)
{
    if (sub_root == NULL){return 0;}
    if (sub_root->data == target){target->deleted ? return  0 : return 1;}
    else if (target < sub_root->data){return search_and_delete(sub_root->left, target);}
    else if (target > sub_root->data){return search_and_delete(sub_root->right, target);}
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
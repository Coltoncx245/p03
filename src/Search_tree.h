template <class Record>
class Search_tree: public Binary_tree<Record>
{
public:
    virtual Error_code insert(const Record &new_data);

    virtual Error_code remove(const Record &target);
    Error_code tree_search(Record &target) const;
protected:
    virtual // Auxiliary functions
    Error_code search_and_insert(Binary_node<Record>* &sub_root, const Record &new_data);

    virtual Error_code search_and_delete(Binary_node<Record>* &sub_root, const Record &target);
    Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, const Record &target) const;
};


template <class Record>
Error_code Search_tree<Record>::insert(const Record &new_data){return search_and_insert(this->root, new_data);}

template <class Record>
Error_code Search_tree<Record>::search_and_insert(Binary_node<Record> *&sub_root,
                                                  const Record &new_data)
{
   if (sub_root == NULL)
   {
       sub_root = new Binary_node<Record>(new_data);
       return success;
   }
   else if (new_data < sub_root->data){return search_and_insert(sub_root->left, new_data);}
   else if (new_data > sub_root->data){return search_and_insert(sub_root->right, new_data);}
   else return duplicate_error;
}

template <class Record>
Error_code Search_tree<Record>::remove(const Record &target){return search_and_delete(this->root, target);}

template <class Record>
Error_code Search_tree<Record>::search_and_delete(Binary_node<Record>* &sub_root,
                                                  const Record &target)
{
   if (sub_root == NULL){return not_present;}
   else if (sub_root->data == target)
   {
      if (sub_root->right == NULL) // No right child
      {
         Binary_node<Record> *to_delete = sub_root;  //  Remember node to delete at end.
         sub_root = sub_root->left;
         delete to_delete;
      }
      else if (sub_root->left == NULL) // No left child
      {
         Binary_node<Record> *to_delete = sub_root;  //  Remember node to delete at end.
         sub_root = sub_root->right;
         delete to_delete;
      }
      else // subroot has two children
      {
         // search for the immediate predecessor 
         Binary_node<Record> *predecessor_node = sub_root->left; 
         while (predecessor_node->right != NULL){predecessor_node = predecessor_node->right;}

         sub_root->data = predecessor_node->data; // replace the target with the immediate predecessor
         search_and_delete(sub_root->left, sub_root->data); // delete the redundant immediate predecessor
      }
   }
   else if (target < sub_root->data){return search_and_delete(sub_root->left, target);}
   else{return search_and_delete(sub_root->right, target);}
   return success;
}


template <class Record>
Error_code Search_tree<Record>::tree_search(Record &target) const
{
   Error_code result = success;
   Binary_node<Record> *found = search_for_node(this->root, target);
   if (found == NULL){result = not_present;}
   else{target = found->data;}
   return result;
}


template <class Record>
Binary_node<Record> *Search_tree<Record>::search_for_node(Binary_node<Record>* sub_root,
                                                          const Record &target) const
{
   if (sub_root == NULL || sub_root->data == target){return sub_root;}
   else if (sub_root->data < target){return search_for_node(sub_root->right, target);}
   else{return search_for_node(sub_root->left, target);}
}

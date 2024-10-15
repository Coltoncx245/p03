#include "utility.h"
#include "Binary_node.h"
#include "Binary_tree.h"
#include "Search_tree.h"


int main(){
   string input;
   bool exit_now = false;
   Search_tree<int> searchTree;
   while(!exit_now){
      cout << endl;
      cout << "***********************" << endl;
      cout << "Menu:" << endl;
      cout << "1. Incremental Insert" << endl;
      cout << "2. Incremental Delete" << endl;
      cout << "c. Clear tree" << endl;
      cout << "p. Print tree" << endl;
      cout << "h. Print tree height" << endl;
      cout << "s. Print tree size" << endl;
      cout << "x. Exit" << endl;
      cout << "***********************" << endl;

      getline(cin, input);

      if(input == "1"){
         cout << endl;
         cout << "Enter new integer keys to insert.  Enter \"q<Enter>\" to quit." << endl;
         cout << endl;
         getline(cin, input);

         while(input != "q"){
            searchTree.insert(string_to_int(input));
            searchTree.print();            
            getline(cin, input);
         }
      } 
      else if(input == "2"){
         cout << endl;
         cout << "Enter integer keys to delete.  Enter \"q<Enter>\" to quit." << endl;
         cout << endl;
         getline(cin, input);
         while(input != "q"){
            searchTree.remove(string_to_int(input));
            searchTree.print();            
            getline(cin, input);
         }
      } 
      else if (input == "c")
         searchTree.clear();
      else if (input == "p")
         searchTree.print();
      else if (input == "h")
         cout << endl << "The height of the binary tree is " << searchTree.height() << endl;
      else if (input == "s")
         cout << endl << "The size (node count) of the binary tree is " << searchTree.size() << endl;
      else if(input == "x")
         exit_now = true;
   }
}

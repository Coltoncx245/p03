#include "utility.h"
#include "Binary_node.h"
#include "Binary_tree.h"
#include "Search_tree.h"

// // Update to pass the correct type for Lazy_tree
// void process_command(const std::string &command, Lazy_tree<int> &tree, std::ofstream &outfile);

int main(int argc, char *argv[])
{
   return 0;
}

////// This is a very rough idea of what I think we're going to have to do logically to parse the input file
////// But uncomment at your own risk
//// Define the correct template parameter for Lazy_tree in the function as well
//void process_command(const std::string &command, Lazy_tree<int> &tree, std::ofstream &outfile) {
//    std::istringstream iss(command);
//    std::string operation;
//    char colon;
//    int key;
//
//    // Parse the operation
//    iss >> operation;
//
//    if (operation == "insert" || operation == "remove") {
//        if (iss >> colon >> key && colon == ':') {
//            if (operation == "insert") {
//                // Check if key is within the valid range and attempt insertion
//                if (key >= 1 && key <= 99) {
//                    outfile << (tree.insert(key) ? "true" : "false") << std::endl;
//                } else {
//                    outfile << "Error: insert (illegal argument: not in range)" << std::endl;
//                }
//            } else if (operation == "remove") {
//                outfile << (tree.remove(key) ? "true" : "false") << std::endl;
//            }
//        } else {
//            outfile << "Error: " << operation << " (no key)" << std::endl;
//        }
//    } else if (operation == "contains") {
//        if (iss >> colon >> key && colon == ':') {
//            outfile << (tree.contains(key) ? "true" : "false") << std::endl;
//        } else {
//            outfile << "Error: contains (no key)" << std::endl;
//        }
//    } else if (operation == "findMin") {
//        outfile << tree.findMin() << std::endl;
//    } else if (operation == "findMax") {
//        outfile << tree.findMax() << std::endl;
//    } else if (operation == "print") {
//        outfile << tree.print() << std::endl;
//    } else if (operation == "height") {
//        outfile << tree.height() << std::endl;
//    } else if (operation == "size") {
//        outfile << tree.size() << std::endl;
//    } else {
//        outfile << "Error: " << operation << " (invalid command)" << std::endl;
//    }
//}

#include "LazyBinarySearchTree.h"

void process_command(std::string &command, std::string &arg, LazyBinarySearchTree &tree, std::ofstream &outfile);
void process_command(std::string &command, LazyBinarySearchTree &tree, std::ofstream &outfile);


int main(int argc, char *argv[])
{

   if (argc > 2)
   {

      LazyBinarySearchTree tree = LazyBinarySearchTree();

      std::ifstream infile(argv[1]);
      std::ofstream outfile(argv[2]);
      std::string line;
      
      while (getline(infile, line))
      {
         try
         {
            std::istringstream sstream(line);
            std::string token;
            std::string token_stack[3] = {"", "", ""};
            int i = 0;

            while (std::getline(sstream,token,':'))
            {
               token_stack[i] = token;
               i++;
            }

            switch (i)
            {
            case 1:
               process_command(token_stack[0], tree, outfile);
               break;
            case 2:
               process_command(token_stack[0], token_stack[1], tree, outfile);
               break;
            default:
               break;
            }
         }
         catch(TreeException& e)
         {
            outfile << e.what() << std::endl;
         }
      }
   }
   else
   {
      std::cout << "Command Line Error\nExpected format: p03 input.dat output.dat" << std::endl;
   }
   
   return 0;
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

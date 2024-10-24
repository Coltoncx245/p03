#include "LazyBinarySearchTree.h"
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

// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    
    // your code goes here...  
    trie *Grammarly = new trie;

    // Create an infinite while loop which can only be exited with "done" command
    while (true){

        // Receive User input
        std::string user_input = "";
        std::getline (std::cin,user_input);
        

        // Call appropriate functions
        if (user_input.find("load") != std::string::npos) {
            std::cout << "load" << std::endl;
        }

        else if (user_input[0] == 'i') {
            std::string paramater = user_input.substr(2);
            Grammarly->insert(paramater);
        }

        else if (user_input[0] == 'c') {
            std::string paramater = user_input.substr(2);
            Grammarly->prefix_command(paramater);
        }

        else if (user_input[0] == 'e') {
            std::string paramater = user_input.substr(2);
            Grammarly->erase(paramater);
            
        }

        else if (user_input[0] == 'p') {
            Grammarly->print();
        }

        else if (user_input.find("spellcheck") != std::string::npos) {
            std::string paramater = user_input.substr(user_input.find(' ') + 1);
            Grammarly->spellcheck(paramater);
        }

        else if (user_input.find("empty") != std::string::npos) {
            
        }

        else if (user_input.find("clear") != std::string::npos) {
            
        }

        else if (user_input.find("size") != std::string::npos) {
            Grammarly->size();
        }


        else{
            // why does exit not exit the program helpppp
            
            // Call the trie destructor and exit the program
            //delete Grammarly;
            break;
            std::cout << "dog" << std::endl;
            exit(0);
        }
    }
}
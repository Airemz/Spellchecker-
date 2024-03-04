// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    
    // your code goes here...  
    trie *Grammarly = new trie;

    // Create an infinite while loop for the game which can only be exited with "OVER" command
    while (true){
        // Receive User input
        std::string user_input = "";
        std::getline (std::cin,user_input);
        
        // Call appropriate functions
        if (user_input.find("load") != std::string::npos) {
            
        }

        else if (user_input.find("i") != std::string::npos) {
            
        }

        else if (user_input.find("c") != std::string::npos) {
            
        }

        else if (user_input.find("e") != std::string::npos) {
            
        }

        else if (user_input.find("p") != std::string::npos) {
            
        }

        else if (user_input.find("spellcheck") != std::string::npos) {
            
        }

        else if (user_input.find("empty") != std::string::npos) {
            
        }

        else if (user_input.find("clear") != std::string::npos) {
            
        }

        else if (user_input.find("size") != std::string::npos) {
            
        }


        else if (user_input.find("exit") != std::string::npos) {
            
            // Call the trie destructor and exit the program
            delete Grammarly;
            exit(0);
        }
    }

}
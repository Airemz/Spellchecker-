// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"


int main(){
    
    // your code goes here...  
    trie *Grammarly = new trie;

    //./spellcheck.out < inputs/test01.in > my_outputs/mtest01.out

    // Create an infinite while loop which can only be exited with "done" command
    while (true){

        // Receive User input
        std::string user_input = "";
        std::getline (std::cin,user_input);
        

        // Call appropriate functions
        if (user_input.find("load") != std::string::npos) {
            std::ifstream file;
            file.open ("corpus.txt");

            std::string word;
            while (file >> word){
                Grammarly->load(word);
            }

            std::cout << "success" << std::endl;
        }

        else if (user_input.find("exit") != std::string::npos) {
            return 0;
        }

        else if (user_input.find("empty") != std::string::npos) {
            Grammarly->empty();
        }

        else if (user_input.find("clear") != std::string::npos) {
            Grammarly->clear();
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

        else if (user_input.find("size") != std::string::npos) {
            Grammarly->size();
        }
    }
}
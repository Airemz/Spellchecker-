// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"


int main(){
    
    // your code goes here...  
    trie *Grammarly = new trie;

    //./spellcheck.out < inputs/test01.in > my_outputs/mtest01.out
    //valgrind --leak-check=full --show-leak-kinds=all ./spellcheck.out <inputs/test03.in 

    // Check e time complexity and edge cases for all functions/more testcases

    // Create an infinite while loop which can only be exited with "exit" command
    while (true){

        // Receive User input
        std::string user_input = "";
        std::getline (std::cin,user_input);
        

        // Call appropriate functions based on input

        // Load: Open given file and extract words until end. Output success after.
        if (user_input.find("load") != std::string::npos) {
            std::ifstream file;
            file.open ("corpus.txt");

            std::string word;
            while (file >> word){
                Grammarly->load(word);
            }

            std::cout << "success" << std::endl;
        }

        // Exit: calls clear function, then call the destructor to delete the root
        else if (user_input.find("exit") != std::string::npos) {
            Grammarly->clear();
            delete Grammarly;
            return 0;
        }

        // Empty: checks if the trie is empty
        else if (user_input.find("empty") != std::string::npos) {
            Grammarly->empty();
        }

        // Clear: delete all the words in the trie,
        else if (user_input.find("clear") != std::string::npos) {
            Grammarly->clear();
        }

        // Insert: extract the word from input and add the word to the tree if possible
        else if (user_input[0] == 'i') {
            std::string paramater = user_input.substr(2);
            Grammarly->insert(paramater);
        }

        // Prefix: extract word and check how many words its a prefix for
        else if (user_input[0] == 'c') {
            std::string paramater = user_input.substr(2);
            Grammarly->prefix(paramater);
        }

        // Erase: extract word from input and delete it from the trie reccursivly
        else if (user_input[0] == 'e') {
            std::string paramater = user_input.substr(2);
            Grammarly->erase(paramater);
            
        }

        // Print: prints all words in the trie
        else if (user_input[0] == 'p') {
            Grammarly->print();
        }

        // Spellcheck: will try correcting a given word with a word in a trie if possible
        else if (user_input.find("spellcheck") != std::string::npos) {
            std::string paramater = user_input.substr(user_input.find(' ') + 1);
            Grammarly->spellcheck(paramater);
        }

        // Size: outputs number of words in the trie
        else if (user_input.find("size") != std::string::npos) {
            Grammarly->size();
        }
    }
}
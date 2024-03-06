#include <iostream>
#include <string>
#include "trie.h"

// node constructor, no need for destructor as this will be deallocated in Trie destructor
node::node(){

    // Initilize boolean and children to nullptr
    end_of_word = false;

    for (int i = 0; i < 26; i++){
        children[i] = nullptr;
    }
}

//////////////////////////////////////////////////////
//////////// Trie Member Functions ////////////
//////////////////////////////////////////////////////

// Constructor
trie::trie(){
    root = new node();
    empty_trie = false;
    number_of_words = 0;
}

// Destructor
trie::~trie(){}

// Trie Helper functions

int trie::prefix_helper(node *node, int &counter){

    // Recurse through all children if they exist
    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            prefix_helper(node->children[i], counter);
            // After recursing check if those children are end of words, if so update counter
            if (node->children[i]->end_of_word == true){counter++;}
        }
    }

    return counter;
}

void trie::print_helper(node *node, std::string output){

    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            char letter = 'a' + i;
            print_helper(node->children[i], output + letter );
        }
    }

    // After recursing check if those children are end of words, if so output
    if (node->end_of_word == true){std::cout << output << " ";}
}

// Search for the node that a word corresponds to
node* trie::search(node *node, std::string word_to_search){

    // Base case: if our string is empty, return the node else return nullptr
    if (word_to_search.empty()){return node;}

    // Traverse the tree recursively 
    int letter_index = word_to_search[0] - 'a';
    
    // If the child node doesn't exist return nullptr
    if (node->children[letter_index] == nullptr){return nullptr;}
    node = node->children[letter_index];
    return search(node, word_to_search.substr(1));

}

void trie::delete_word(node *current_node, std::string word_to_delete){

    // Base case: if our string is empty delete that node
    if (word_to_delete.empty()){
        std::cout << "deleted" << std::endl;
        number_of_words--;
        delete current_node;
        current_node = nullptr;
        return;
    }

    // Traverse the tree recursively 
    int letter_index = word_to_delete[0] - 'a';
    
    delete_word(current_node->children[letter_index], word_to_delete.substr(1));

    if (current_node->children[letter_index] == nullptr){std::cout << "deleted fr" << std::endl;}
    

    // Check if the parent node has any children after deleting, if not delete the parent
    for (int i = 0; i < 26; i++){
        std::cout << "index: " << i << std::endl;
        if (current_node->children[i] != nullptr || current_node == root){return;}
        
    }


    std::cout << "deleted parent " << std::endl;
    // parent->end_of_word = false;
    // number_of_words--;
    delete current_node;
    current_node = nullptr;
    return;
}

void trie::spellcheck_helper1(node *node, std::string input, std::string output){

    // Basecase
    if (input.empty()){return;}

    // Traverse the tree recursively 
    int letter_index = input[0] - 'a';
    
    // If the letter doesn't exist return
    if (node->children[letter_index] == nullptr){return;}
    char letter = 'a' + letter_index;
    spellcheck_helper1(node->children[letter_index], input.substr(1), output + letter);
    if (node == root) {return;}
    spellcheck_helper2(node, output);
}

void trie::spellcheck_helper2(node *node, std::string output){

    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            char letter = 'a' + i; 
            // After recursing check if those children are end of words, if so output
            if (node->children[i]->end_of_word == true){std::cout << output+letter << " ";}
            spellcheck_helper2(node->children[i], output + letter);
        }
    }

    
}

// Trie command functions
void trie::load(){}

void trie::insert(std::string word){

    // Temp node for iterrating through tree
    node *current = root;

    // Itterate through the word and add the letter node if it isn't a child
    for (unsigned i = 0; i < word.length(); i++){

        // Index of the current letter in the word (z-a = 25) which will be the 25th index in the childrens array
        int letter_index = word[i] - 'a';

        // Check if that child node is nullptr, if so create it
        if (current->children[letter_index] == nullptr){
            current->children[letter_index] = new node;
        }

        // Go to that child node after creating/created and add children for next letters
        current = current->children[letter_index];
        
    }

    // Check if the last letter(node) is already a word and output accoridingly
    if (current->end_of_word == false){

        // Updating vars
        current->end_of_word = true;
        empty_trie = false;
        number_of_words++;

        std::cout << "success" << std::endl;

    } else{std::cout << "failure" << std::endl;}

    // Deallocate temp node
    // delete current;
    // current = nullptr;
}

void trie::prefix_command(std::string prefix){

    // Search for the word in the tree, if it doesn't exist output not found
    node* found_node = search(root, prefix);

    if (found_node == nullptr){std::cout << "not found" << std::endl;}

    else{
        int inital_counter = 0;

        // Check if the given prefix is the end of a word
        if (found_node->end_of_word == true){inital_counter++;}

        // Call helper function with inital counter 0
        int count = prefix_helper(found_node, inital_counter);
        std::cout << "count is: " << count << std::endl;
        
    }
}

void trie::erase(std::string word){

    // Search for the word in the tree, if it doesn't exist output failure
    node* found_node = search(root, word);

    if (found_node == nullptr){std::cout << "failure" << std::endl;}
    else{

        delete_word(root,word);
        std::cout << "success" << std::endl;
    }

}

void trie::print(){
    if (!empty_trie){print_helper(root, "");}
    std::cout << std::endl;
}

void trie::spellcheck(std::string word){

    // Search for the word in the tree, if it exists print correct
    node* found_node = search(root, word);

    if (found_node != nullptr && found_node->end_of_word){std::cout << "correct" << std::endl;}
    else{
        
        spellcheck_helper1(root, word, "");
        std::cout << std::endl;
    }
}

void trie::empty(){
    if (empty_trie) {std::cout << "empty 1" << std::endl;}
    else{std::cout << "empty 0" << std::endl;}
}

void trie::clear(){}

void trie::size(){
    std::cout << number_of_words << std::endl;
}
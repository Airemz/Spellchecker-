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

void trie::print_helper(node *&node){
    
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

    // Base case: if our string is empty
    // If it is the end of the word, delete that node
    if (word_to_delete.empty()){
        delete current_node;
        current_node = nullptr;
        return;
    }

    // Traverse the tree recursively 
    int letter_index = word_to_delete[0] - 'a';
    node *parent = current_node;
    current_node = current_node->children[letter_index];
    delete_word(current_node, word_to_delete.substr(1));

    // Check if the parent node has any children after deleting, if not delete the parent
    for (int i = 0; i<26; i++){
        if (parent->children[i] != nullptr || parent == root){return;}
    }

    delete parent;
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

};
void trie::print(){
    print_helper(root);
}

void trie::spellcheck(std::string word){};
void trie::empty(){};
void trie::clear(){};
void trie::size(){};
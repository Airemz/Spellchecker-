#include <iostream>
#include <string>
#include <fstream>
#include "trie.h"

// node constructor, no need for destructor as this will be deallocated in Trie destructor
node::node(){

    // Initilize boolean and children to nullptr
    end_of_word = false;
    num_of_children = 0;

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

void trie::print_helper(node *node, std::string &output){

    if (node->end_of_word == true){std::cout << output << " ";}
    //std::cout << output << " ";

    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            
            char letter = 'A' + i;
            output.push_back(letter);
            print_helper(node->children[i], output);
            output.pop_back();
        }
    }
}

// Search for the node that a word corresponds to
node* trie::search(node *node, std::string &word_to_search, unsigned int index = 0){

    // Base case: if our string is empty, return the node else return nullptr
    if (index == word_to_search.length()){return node;}

    // Traverse the tree recursively 
    int letter_index = word_to_search[index] - 'A';
    
    // If the child node doesn't exist return nullptr
    if (node->children[letter_index] == nullptr){return nullptr;}
    node = node->children[letter_index];
    return search(node, word_to_search, index + 1);

}

void trie::delete_node(node *current_node, int index){
    if (current_node->children[index]->end_of_word){number_of_words--;}
    current_node->num_of_children--;
    delete current_node->children[index];
    current_node->children[index] = nullptr;
    
    if (number_of_words == 0){empty_trie = true;}
}

void trie::erase_helper(node *current_node, std::string &word_to_delete, bool &deleted, unsigned int index = 0){
    
    // Basecase: index is at the last letter, retun so its the second last letter
    if (index == word_to_delete.length()){return;}

    // Traverse the tree recursively until at the last letter
    int letter_index = word_to_delete[index] - 'A';
    
    erase_helper(current_node->children[letter_index], word_to_delete, deleted, index + 1);

    // Stop deleting if the node is end of word and we already deleted desired word
    if (current_node->children[letter_index]->end_of_word && deleted){return;}

    // Check if leaf node
    else if (current_node->children[letter_index]->num_of_children == 0){
        delete_node(current_node,letter_index);
        deleted = true;
    }

    // Check if the word is in the trie, but a prefix of another word
    else if (current_node->children[letter_index]->end_of_word){
        current_node->children[letter_index]->end_of_word = false;
        number_of_words--;
        deleted = true;
    }
        
}

// Recurse to the last letter in the word adding the letters to the ouput with each recursion. Check if the word has any words in the trie using the second helper function. If so output the words and return true, so no more words are outputted.

void trie::spellcheck_helper1(node *node, std::string &input, std::string &output, bool &tracker, unsigned int index = 0 ){

    // Basecase: reached last letter
    if (index == input.length()){return;}

    // Traverse the tree recursively 
    int letter_index = input[index] - 'A';
    
    // If the letter doesn't exist return
    if (node->children[letter_index] == nullptr){return;}
    char letter = 'A' + letter_index;
    output.push_back(letter);

    spellcheck_helper1(node->children[letter_index], input, output, tracker, index + 1);
    
    // Send the words to second helper function, if any words are in the trie and words are outputted, the tracker will stop those words from being outputted again.
    if (tracker == false){
        if(spellcheck_helper2(node->children[letter_index], output, tracker)){tracker = true;};
        
    } else {return;}
}

bool trie::spellcheck_helper2(node *node, std::string &output, bool &tracker){

    // Basecase: node is end of word
    if (node->end_of_word){
        std::cout << output << " ";
        tracker = true;
    }
    
    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            char letter = 'A' + i; 
            
            // After recursing check if those children are end of words, if so output
            output.push_back(letter);
            spellcheck_helper2(node->children[i], output, tracker);
            output.pop_back();
        }
    }

    return tracker;
}

void trie::clear_helper(node *node){

    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
        
            clear_helper(node->children[i]);
            // After recursing check if those children are end of words, if so output
            delete_node(node,i);
        }
    }
}

// Trie command functions
void trie::load(std::string word){

    // Temp node for iterrating through tree
    node *current = root;

    // Itterate through the word and add the letter node if it isn't a child
    for (unsigned int i = 0; i < word.length(); i++){

        // Index of the current letter in the word (z-a = 25) which will be the 25th index in the childrens array
        int letter_index = word[i] - 'A';

        // Check if that child node is nullptr, if so create it
        if (current->children[letter_index] == nullptr){
            current->num_of_children++;
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

    } 
}

void trie::insert(std::string word){

    // Temp node for iterrating through tree
    node *current = root;

    // Itterate through the word and add the letter node if it isn't a child
    for (unsigned int i = 0; i < word.length(); i++){

        // Index of the current letter in the word (z-a = 25) which will be the 25th index in the childrens array
        int letter_index = word[i] - 'A';

        // Check if that child node is nullptr, if so create it
        if (current->children[letter_index] == nullptr){
            current->num_of_children++;
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
        std::cout << "count is " << count << std::endl;
        
    }
}

void trie::erase(std::string word){

    // Search for the word in the tree, if it doesn't exist output failure
    node* found_node = search(root, word);

    if (found_node == nullptr || found_node->end_of_word == false){std::cout << "failure" << std::endl;}
    else{
        bool deleted = false;
        erase_helper(root,word, deleted);
        std::cout << "success" << std::endl;
    }

}

void trie::print(){
    std::string empty_string = "";
    if (!empty_trie){
        print_helper(root, empty_string);
        std::cout << std::endl;
    }
}

void trie::spellcheck(std::string word){

    // Search for the word in the tree, if it exists print correct
    node* found_node = search(root, word);

    if (found_node != nullptr && found_node->end_of_word){std::cout << "correct" << std::endl;}

    else if(empty_trie){return;}

    else{
        
        // Check if there are any prefixes in the trie with the word
        int inital_counter = 0;
        int count = prefix_helper(root, inital_counter);

        // If there are at any prefixes call the spellcheck function
        if (count > 0){
            std::string empty_string = "";
            bool tracker = false;
            spellcheck_helper1(root, word, empty_string, tracker);    
        }
        
        // Always output a new line
        std::cout << std::endl;
    }
}

void trie::empty(){
    if (empty_trie) {std::cout << "empty 1" << std::endl;}
    else{std::cout << "empty 0" << std::endl;}
}

void trie::clear(){
    if (!empty_trie){clear_helper(root);}
    std::cout << "success" << std::endl;
}

void trie::size(){
    std::cout << "number of words is " << number_of_words << std::endl;
}
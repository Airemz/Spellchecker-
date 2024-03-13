#include <iostream>
#include <string>
#include "trie.h"

// Node constructor, no need for destructor as this is deallocated automatically when deleting nodes/trie
node::node(){

    // Initilize boolean, number of children upon creating a node
    end_of_word = false;
    num_of_children = 0;

    // Initialize all children to nullptr
    for (int i = 0; i < 26; i++){
        children[i] = nullptr;
    }
}


//////////////////////////////////////////////////////
/////////////// Trie Member Functions ////////////////
//////////////////////////////////////////////////////

// Constructor - initialize the root and private vars
trie::trie(){
    root = new node();
    empty_trie = true;
    number_of_words = 0;
}

// Destructor - simply delete the root since the tree is empty
trie::~trie(){
    delete root;
}

//////////////////////////////////////////////////////
/////////////// Trie Helper Functions ////////////////
//////////////////////////////////////////////////////

int trie::prefix_helper(node *node, int &counter){

    // Recurse through all children if they exist
    for (int i = 0; i < 26; i++){

        // Check if children exists, if so recurse through the grandchildren
        if (node->children[i] != nullptr){
            prefix_helper(node->children[i], counter);

            // After recursing check if those children are end of words, if so update counter since it is pass-by-reference
            if (node->children[i]->end_of_word == true){counter++;}
        }
    }

    // Return the final counter after checking all children
    return counter;
}

void trie::print_helper(node *node, std::string &output){
    
    // Basecase: if current node is the end of a word, output the word
    if (node->end_of_word == true){std::cout << output << " ";}

    // Itterate through children
    for (int i = 0; i < 26; i++){

        // Check if the node has any children
        if (node->children[i] != nullptr){
            
            // Extract child letter and push to the output string, then recurse through the grandchildren
            char letter = 'A' + i;
            output.push_back(letter);
            print_helper(node->children[i], output);

            // Pop the letter from the output so that other children dont have the wrong letter
            output.pop_back();
        }
    }
}

// Search for the node that a word corresponds to if it does exist. Useful for many trie functions. Time complexity is O(n) where n = number of letters in given word
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

// Used by erase helper function to delete a child node. Function params are the parent node and the index of the child to delete
void trie::delete_node(node *current_node, int index){

    // Updating node vars
    if (current_node->children[index]->end_of_word){number_of_words--;}
    current_node->num_of_children--;

    // Deleting node
    delete current_node->children[index];
    current_node->children[index] = nullptr;
    
    // Update trie private var
    if (number_of_words == 0){empty_trie = true;}
}

// Erase a word by recursing to the second last letter, then deleting the nodes child accoring to various cases. The flag is used to stop deleting unintended words and the index is used for itterating through the word.
void trie::erase_helper(node *current_node, std::string &word_to_delete, bool &flag, unsigned int index = 0){
    
    // Basecase: index is at the last letter, retun so its the second last letter
    if (index == word_to_delete.length()){return;}

    // Extract letter index from the word with O(1)
    int letter_index = word_to_delete[index] - 'A';
    
    // Recurse through children until current node is at second last letter
    erase_helper(current_node->children[letter_index], word_to_delete, flag, index + 1);

    // Check if the node is the end of a word and if our flag is true meaning a word was deleted already, if so do return
    if (current_node->children[letter_index]->end_of_word && flag){return;}

    // Check if leaf node, meaning node has no children
    else if (current_node->children[letter_index]->num_of_children == 0){

        // Delete the child node and initialize the flag so that no unintended words are deleted
        delete_node(current_node,letter_index);
        flag = true;
    }

    // Finally, check if the word is in the trie, but is a prefix of another word and we didnt delete yet
    else if (current_node->children[letter_index]->end_of_word){

        // Update node, trie vars and flag
        current_node->children[letter_index]->end_of_word = false;
        number_of_words--;
        flag = true;
    }   
}

// Recurse to the second last letter of the word adding the letters to the ouput with each recursion. The flag will be used to stop outputting words after the word with the maximum common prefix was outputted and the index is used for itterating through the word.
void trie::spellcheck_helper_traverse(node *node, std::string &input, std::string &output, bool &flag, unsigned int index = 0 ){

    // Basecase: reached last letter
    if (index == input.length()){return;}

    // Extract letter index from the word with O(1)
    int letter_index = input[index] - 'A';
    
    // If the letter doesn't exist return
    if (node->children[letter_index] == nullptr){return;}
    char letter = 'A' + letter_index;
    output.push_back(letter);

    // Recurse through children until current node is at second last letter
    spellcheck_helper_traverse(node->children[letter_index], input, output, flag, index + 1);
    
    // Send the output to spellcheck print helper function, if any words are in the trie and words are printed, the flag will stop those words from being printed again with following instances of recursion.
    if (flag == false){
        if(spellcheck_helper_print(node->children[letter_index], output, flag)){flag = true;};
        
    } else {return;}
}

// Recurse through nodes children and output if those are end of words. The flag is used to determine if any words were outputted. If so the function will return true to the spellcheck traverse function which will prevent copies of the same word from being outputted
bool trie::spellcheck_helper_print(node *node, std::string &output, bool &flag){

    // Basecase: node is end of word
    if (node->end_of_word){
        std::cout << output << " ";

        // A word was outputted so set the flag is set to true
        flag = true;
    }
    
    for (int i = 0; i < 26; i++){

        // Check if the node has any children
        if (node->children[i] != nullptr){
            
            // Extract child letter and push to the output string, then recurse through the grandchildren
            char letter = 'A' + i; 
            output.push_back(letter);
            spellcheck_helper_print(node->children[i], output, flag);

            // Pop the letter from the output so that other children dont have the wrong letter
            output.pop_back();
        }
    }

    // Return flag to the orignal traverse function
    return flag;
}

// Recurse all the way through each child and delete recursively.
void trie::clear_helper(node *node){

    // Itterate through all children of the current node
    for (int i = 0; i < 26; i++){

        // Check if any children exists
        if (node->children[i] != nullptr){
        
            // Recurse through the grandchildren
            clear_helper(node->children[i]);

            // After recursing check if those children are end of words, if so output
            delete_node(node,i);
        }
    }
}

//////////////////////////////////////////////////////
/////////////// Trie Command Functions ///////////////
//////////////////////////////////////////////////////

// Load the corpus file into the trie. This function is the exact same as the insert function except it doesn't output success/failure with each word. Time complexity is irrelevant.
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

// Adds a word to the trie itteratively checking if that child already exists or not. After adding all the letters, update node and trie variables, and output accordingly. 
// O(n)
void trie::insert(std::string word){

    // Temp node for iterrating through tree
    node *current = root;

    // Itterate through the word until at the last letter
    for (unsigned int i = 0; i < word.length(); i++){

        // Index of the current letter in the word (z-a = 25) which will be the 25th index in the childrens array
        int letter_index = word[i] - 'A';

        // Check if that child node is nullptr, if so create it and update the current nodes number of children variable
        if (current->children[letter_index] == nullptr){
            current->num_of_children++;
            current->children[letter_index] = new node;
        }

        // Go to that child node after creating/created and add children for next letters
        current = current->children[letter_index];
        
    }

    // Check if the last letter(node) is not a word and output accoridingly
    if (current->end_of_word == false){

        // Updating vars
        current->end_of_word = true;
        empty_trie = false;
        number_of_words++;

        std::cout << "success" << std::endl;

    } else{std::cout << "failure" << std::endl;}
}

// Checks how many words the given word is a prefix for and outputs that number 
// O(N)
void trie::prefix(std::string prefix){

    // Search for the word in the tree, 
    node* found_node = search(root, prefix);

    // If it doesn't exist output not found since we can't prefix for anything
    if (found_node == nullptr){std::cout << "not found" << std::endl;}

    // Check if the trie is empty
    else if(empty_trie){return;}

    else{
        int inital_counter = 0;

        // Check if the given prefix is the end of a word, update counter
        if (found_node->end_of_word == true){inital_counter++;}

        // Call helper function to recurse through nodes with inital counter 0
        int final_count = prefix_helper(found_node, inital_counter);
        std::cout << "count is " << final_count << std::endl;
        
    }
}

// Erase a word from the trie if possible 
// O(n)
void trie::erase(std::string word){

    // Search for the word in the tree, if it doesn't exist output failure
    node* found_node = search(root, word);

    if (found_node == nullptr || found_node->end_of_word == false){std::cout << "failure" << std::endl;}

    // Check if the trie is empty
    else if(empty_trie){return;}

    else{
        // Initialize the flag and call the recursive helper function. Then output success
        bool flag = false;
        erase_helper(root,word, flag);
        std::cout << "success" << std::endl;
    }
}

// Print all words in the trie. 
// O(N)
void trie::print(){

    // If the trie is empty, do nothing as stated on piazza
    if (empty_trie){return;}

    // Since the trie is not empty, output the words and end the line
    else{
        
        // Initialize an empty string for outputting and call the recursive helper function. When all words are outputted, end the line.
        std::string empty_string = "";
        print_helper(root, empty_string);
        std::cout << std::endl;
    }

}

// Check if the given word is in the trie, if so output correct. Else suggest word(s) in the trie with the most common prefix 
// O(N)
void trie::spellcheck(std::string word){

    // Search for the word in the tree, if it exists and is a valid word, print correct
    node* found_node = search(root, word);

    if (found_node != nullptr && found_node->end_of_word){std::cout << "correct" << std::endl;}

    // Check if the trie is empty, if so output a blank line
    else if(empty_trie){std::cout << std::endl;}

    else{
        
        // Initialize the empty string for output, the flag and call the recursive helper function. Then output an empty line
        std::string empty_string = "";
        bool flag = false;
        spellcheck_helper_traverse(root, word, empty_string, flag);    
        
        // Always outpifut a new line
        std::cout << std::endl;
    }
}

// Check if the trie is empty 
// O(1)
void trie::empty(){
    // Check if the trie private variable is true and output accordingly
    if (empty_trie) {std::cout << "empty 1" << std::endl;}
    else{std::cout << "empty 0" << std::endl;}
}

// Delete all words(nodes) from the trie
// O(N)
void trie::clear(){
    
    // Check if the trie is already empty, if not call reccursive helper function and set the trie as empty after
    if (!empty_trie){
        clear_helper(root);
        empty_trie = true;
    }

    
    // Always output success
    std::cout << "success" << std::endl;
}

// Exact same as clear except output nothing.
// No Time complexity
void trie::exit(){
    
    // Check if the trie is already empty, if not call reccursive helper function and set the trie as empty
    if (!empty_trie){
        clear_helper(root);
        empty_trie = true;
    }
}

// Output number of words in the trie
// O(1)
void trie::size(){

    // Simply output the trie private var
    std::cout << "number of words is " << number_of_words << std::endl;
}
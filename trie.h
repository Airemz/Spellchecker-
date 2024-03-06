// define your classes here...
#include <iostream>
#include <string>

struct node{
    
    // Each node contains an array of node pointers of size 26 (one child per alphabet letter)
    node *children[26];

    // Indicates node is an end of a word
    bool end_of_word;

    // Constructor  
    node();
};

class trie{

    private:

        // Variables used in many member functions
        node *root;
        bool empty_trie;
        int number_of_words;

    public:

        // Constructor and destructor
        trie();
        ~trie();

        // Trie Helper functions
        int prefix_helper(node *node, int &counter);
        node* search(node *node, std::string word_to_search);
        void delete_word(node *node, std::string word_to_delete);
        void print_helper(node *node, std::string output);
        void spellcheck_helper1(node *node, std::string input, std::string output);
        void spellcheck_helper2(node *node, std::string output);

        // Trie functions
        void load();
        void insert(std::string word);
        void prefix_command(std::string prefix);
        void erase(std::string word);
        void print();
        void spellcheck(std::string word);
        void empty();
        void clear();
        void size();
};

/* Pseudocode

insert --> done

prefix --> reccursively check all children of word and how many are words




*/ 

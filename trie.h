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


        // Trie functions
        void load();
        void insert(std::string word);
        void prefix(std::string prefix);
        void erase(std::string word);
        void print();
        void spellcheck(std::string word);
        void empty();
        void clear();
        void size();
};
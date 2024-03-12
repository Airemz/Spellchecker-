// define your classes here...
#include <iostream>
#include <string>

// Structure node since we want all members to be public
struct node{
    
    // Each node contains an array of node pointers of size 26 (one child per alphabet letter)
    node *children[26];

    // Important variables used for many trie member functions
    bool end_of_word;
    int num_of_children;

    // Constructor
    node();
};

// Trie Class consisting of many private and public members
class trie{

    private:

        /// Important variables used for many trie member functions
        node *root;
        bool empty_trie;
        int number_of_words;

    public:

        // Constructor and destructor
        trie();
        ~trie();

        // Trie Helper Functions (explained in cpp)
        int prefix_helper(node *node, int &counter);
        node* search(node *node, std::string &word_to_search, unsigned int index);
        void delete_node(node *current_node, int index);
        void erase_helper(node *node, std::string &word_to_delete, bool &flag, unsigned int index);
        void print_helper(node *node, std::string &output);
        void spellcheck_helper_traverse(node *node, std::string &input, std::string &output, bool &flag, unsigned int index);
        bool spellcheck_helper_print(node *node, std::string &output, bool &flag);
        void clear_helper(node *node);

        // Trie Command Functions (explained in cpp)
        void load(std::string word);
        void insert(std::string word);
        void prefix(std::string prefix);
        void erase(std::string word);
        void print();
        void spellcheck(std::string word);
        void empty();
        void clear();
        void size();
};
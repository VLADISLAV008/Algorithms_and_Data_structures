#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Trie {
public:
    explicit Trie(int alphabet_length) {
        this->alphabet_length = alphabet_length;
        root = create_node();
    }

    ~Trie() { deallocateMemory(root); }

    void add_pattern(string pattern) {
        Node *node = root;
        for (int i = 0; i < pattern.length(); i++) {
            int character = pattern[i] - 'a';
            if (node->children[character] == NULL) {
                node->children[character] = create_node();
            }
            node = node->children[character];
        }
        node->is_terminal = true;
        node->count++;
    }

    vector<string> get_sorted() {
        vector<string> result;
        get_sorted(root, "", &result);
        return result;
    }

private:
    struct Node {
        vector<Node *> children;
        bool is_terminal;
        int count;
    };

    int alphabet_length;
    Node *root;

    Node *create_node() {
        vector<Node *> children(alphabet_length);
        return new Node{children, false, 0};
    }

    void get_sorted(Node *node, string current_word, vector<string> *result) {
        if (node->is_terminal) {
            for (int i = 0; i < node->count; i++) {
                result->push_back(current_word);
            }
        }

        for (int i = 0; i < alphabet_length; i++) {
            if (node->children[i] != NULL) {
                char character = 'a' + i;
                get_sorted(node->children[i], current_word + character, result);
            }
        }
    }

    void deallocateMemory(Node *node) {
        for (int i = 0; i < alphabet_length; i++) {
            if (node->children[i] != NULL) {
                deallocateMemory(node->children[i]);
            }
        }
        delete node;
        node = NULL;
    }
};
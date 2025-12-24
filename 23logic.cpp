#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* =========================================================
   In the Worker Knowledge Transfer System, workers type
   keywords like "safety", "maintenance", or "calibration"
   during shift handover. Trie allows instant lookup of
   such tacit knowledge using partial or full keywords.
   ========================================================= */

class TrieNode {
public:
    bool end;                 // Marks completion of a worker note / keyword
    TrieNode* next[26];       // Links to next characters (a–z)

    TrieNode() {
        end = false;
        // Initially, no keyword paths exist
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;   // Entry point for all stored worker keywords

public:
    Trie() {
        // Root represents the starting point of all knowledge keywords
        root = new TrieNode();
    }

    /*
    insert():
    Captures tacit worker knowledge by storing keywords
    such as machine issues, safety tips, or quick fixes.
    */
    void insert(string s) {
        TrieNode* curr = root;

        for (char c : s) {
            int idx = c - 'a';

    
            if (!curr->next[idx])
                curr->next[idx] = new TrieNode();

            curr = curr->next[idx];
        }

        // Marks the keyword as a complete, searchable insight
        curr->end = true;
    }

   
    bool search(string s) {
        TrieNode* curr = root;

        for (char c : s) {
            int idx = c - 'a';

            // If path breaks, the knowledge does not exist
            if (!curr->next[idx])
                return false;

            curr = curr->next[idx];
        }

        // Keyword path exists → knowledge found
        return true;
    }
};

/* =========================================================
  
   In the system, knowledge is grouped into categories
   like Electrical, Mechanical, Safety, etc.
   A 2–3 Tree keeps these categories balanced so that
   lookup time remains predictable even as data grows.
   ========================================================= */

class Node23 {
public:
    string key1, key2;    // Stores one or two knowledge categories
    bool twoKeys;         // Indicates whether node is a 2-node or 3-node

    Node23* left;
    Node23* middle;
    Node23* right;

    Node23(string key) {
        key1 = key;       // First category inserted
        twoKeys = false;  // Starts as a 2-node
        left = middle = right = nullptr;
    }
};

class Tree23 {
public:
    Node23* root;

    Tree23() {
        // Initially, no categories are stored
        root = nullptr;
    }

    
    void insert(string key) {
        if (!root) {
            // First category becomes the root
            root = new Node23(key);
            return;
        }

        // Simplified insertion for demonstration:
        // Adds second category to the root
        if (!root->twoKeys) {
            root->key2 = key;
            root->twoKeys = true;
        }
    }

    /*
    display():
    Shows available knowledge categories
    so workers know where to look for information.
    */
    void display(Node23* node) {
        if (!node) return;

        cout << node->key1 << " ";
        if (node->twoKeys)
            cout << node->key2 << " ";

        cout << endl;
    }
};


int main() {

    // Trie stores searchable worker insights
    Trie trie;

    // 2–3 Tree stores structured knowledge categories
    Tree23 knowledgeCategories;

    // Capturing tacit knowledge during outgoing shift
    trie.insert("safety");
    trie.insert("maintenance");
    trie.insert("calibration");

    // Organizing insights into balanced categories
    knowledgeCategories.insert("Electrical");
    knowledgeCategories.insert("Mechanical");

    // Incoming worker searches for existing knowledge
    cout << "Search 'main': "
         << (trie.search("main") ? "Found" : "Not Found") << endl;

    // Displaying available knowledge domains
    cout << "\nKnowledge Categories Stored (2-3 Tree):\n";
    knowledgeCategories.display(knowledgeCategories.root);

    return 0;
}

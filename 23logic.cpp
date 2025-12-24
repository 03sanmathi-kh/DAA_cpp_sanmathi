#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* ======================= TRIE ======================= */

class TrieNode {
public:
    bool end;
    TrieNode* next[26];

    TrieNode() {
        end = false;
        for (int i = 0; i < 26; i++) next[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string s) {
        TrieNode* curr = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!curr->next[idx])
                curr->next[idx] = new TrieNode();
            curr = curr->next[idx];
        }
        curr->end = true;
    }

    bool search(string s) {
        TrieNode* curr = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!curr->next[idx]) return false;
            curr = curr->next[idx];
        }
        return true;
    }
};

/* ======================= SIMPLE 2-3 TREE ======================= */

class Node23 {
public:
    string key1, key2;
    bool twoKeys;
    Node23* left;
    Node23* middle;
    Node23* right;

    Node23(string key) {
        key1 = key;
        twoKeys = false;
        left = middle = right = nullptr;
    }
};

class Tree23 {
public:
    Node23* root;

    Tree23() {
        root = nullptr;
    }

    // Very simplified insertion for demonstration
    void insert(string key) {
        if (!root) {
            root = new Node23(key);
            return;
        }

        if (!root->twoKeys) {
            root->key2 = key;
            root->twoKeys = true;
        }
    }

    void display(Node23* node) {
        if (!node) return;
        cout << node->key1 << " ";
        if (node->twoKeys)
            cout << node->key2 << " ";
        cout << endl;
    }
};

/* ======================= MAIN ======================= */

int main() {
    Trie trie;
    Tree23 knowledgeCategories;

    trie.insert("safety");
    trie.insert("maintenance");
    trie.insert("calibration");

    knowledgeCategories.insert("Electrical");
    knowledgeCategories.insert("Mechanical");

    cout << "Search 'main': "
         << (trie.search("main") ? "Found" : "Not Found") << endl;

    cout << "\nKnowledge Categories Stored (2-3 Tree):\n";
    knowledgeCategories.display(knowledgeCategories.root);

    return 0;
}

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;


/* Trie to store keywords from worker notes for fast lookup */

class TrieNode {
public:
    bool isEnd;
    map<char, TrieNode*> children;

    TrieNode() {
        isEnd = false;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert keyword into Trie
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    // Check if prefix exists
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                return false;
            curr = curr->children[c];
        }
        return true; // prefix match allowed
    }
};

/* SKIP List */
/* Maintains chronological shift logs */

class SkipNode {
public:
    int timestamp;
    string note;
    vector<SkipNode*> forward;

    SkipNode(int level, int time, string n)
        : timestamp(time), note(n), forward(level + 1, nullptr) {}
};

class SkipList {
    int MAX_LEVEL;
    float probability;
    int level;
    SkipNode* header;

public:
    SkipList(int maxLvl = 5, float p = 0.5) {
        MAX_LEVEL = maxLvl;
        probability = p;
        level = 0;
        header = new SkipNode(MAX_LEVEL, -1, "");
    }

    int randomLevel() {
        int lvl = 0;
        while ((float)rand() / RAND_MAX < probability && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    // Insert shift update
    void insert(int time, string note) {
        vector<SkipNode*> update(MAX_LEVEL + 1);
        SkipNode* curr = header;

        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->timestamp < time)
                curr = curr->forward[i];
            update[i] = curr;
        }

        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++)
                update[i] = header;
            level = newLevel;
        }

        SkipNode* newNode = new SkipNode(newLevel, time, note);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // Display recent logs
    void display() {
        SkipNode* curr = header->forward[0];
        while (curr) {
            cout << "[" << curr->timestamp << "] " << curr->note << endl;
            curr = curr->forward[0];
        }
    }
};



int main() {
    Trie keywordIndex;
    SkipList shiftLogs;
    map<int, vector<string>> priorityNotes; // Red-Black Tree

    // Simulated worker inputs
    keywordIndex.insert("overheat");
    keywordIndex.insert("conveyor");
    keywordIndex.insert("lubrication");

    shiftLogs.insert(1010, "Machine A overheats after 3 hours");
    shiftLogs.insert(1030, "Lubricate conveyor belt every shift");

    priorityNotes[1].push_back("Emergency shutdown if temperature > 90C");
    priorityNotes[2].push_back("Routine belt alignment tip");

    cout << "Keyword Search: 'over' → "
         << (keywordIndex.search("over") ? "Found" : "Not Found") << endl;

    cout << "\nRecent Shift Logs:\n";
    shiftLogs.display();

    cout << "\nPriority-based Insights:\n";
    for (auto &p : priorityNotes) {
        cout << "Priority " << p.first << ":\n";
        for (string note : p.second)
            cout << " - " << note << endl;
    }

    return 0;
}

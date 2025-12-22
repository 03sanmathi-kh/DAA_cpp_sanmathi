#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
PROBLEM STATEMENT:
Given a log file, detect repeated suspicious patterns such as
fraudulent vendor IDs or repeated login attempts.

WHY RABIN-KARP:
Rabin-Karp uses hashing to quickly detect substring matches in
large logs, reducing unnecessary comparisons.
*/

// Calculate hash of a string window
int calculateHash(const string &str, int length) {
    int hash = 0;
    for (int i = 0; i < length; i++)
        hash += str[i];
    return hash;
}

// Check equality after hash matches
bool isEqual(const string &text, const string &pattern, int start) {
    return text.substr(start, pattern.length()) == pattern;
}

// Rabin-Karp search with occurrence count
vector<int> rabinKarpSearch(const string &text, const string &pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();

    if (m == 0 || n == 0 || m > n) return positions;

    int pHash = calculateHash(pattern, m);
    int tHash = calculateHash(text, m);

    for (int i = 0; i <= n - m; i++) {

        if (pHash == tHash) {
            if (isEqual(text, pattern, i))
                positions.push_back(i);
        }

        if (i < n - m)
            tHash = tHash - text[i] + text[i + m];
    }
    return positions;
}

// Read log from user
string readLog() {
    string logText;
    getline(cin, logText);
    return logText;
}

// Read suspicious pattern from user
string readPattern() {
    string pattern;
    getline(cin, pattern);
    return pattern;
}

// Display search results
void displayResults(const vector<int> &positions, const string &pattern) {
    if (positions.empty()) {
        cout << "No suspicious patterns found for \"" << pattern << "\"." << endl;
    } else {
        cout << "Suspicious pattern \"" << pattern << "\" found at positions: ";
        for (int pos : positions)
            cout << pos << " ";
        cout << "\nTotal occurrences: " << positions.size() << endl;
    }
}

// Controller function
void detectSuspiciousPatterns() {
    cout << "Enter log text: ";
    string log = readLog();

    cout << "Enter pattern to detect: ";
    string pattern = readPattern();

    if (log.empty() || pattern.empty()) {
        cout << "Invalid input! Log or pattern cannot be empty." << endl;
        return;
    }

    vector<int> positions = rabinKarpSearch(log, pattern);
    displayResults(positions, pattern);
}

int main() {
    detectSuspiciousPatterns();
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// Detects repeated suspicious patterns using hashing
void rabinKarp(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int pHash = 0, tHash = 0, base = 101;

    // Calculate hash of pattern and first window
    for (int i = 0; i < m; i++) {
        pHash += pattern[i];
        tHash += text[i];
    }

    // Slide pattern over log text
    for (int i = 0; i <= n - m; i++) {
        // Hash match → possible fraud pattern
        if (pHash == tHash) {
            if (text.substr(i, m) == pattern)
                cout << "Suspicious repeated pattern at index " << i << endl;
        }

        // Update hash for next window
        if (i < n - m)
            tHash = tHash - text[i] + text[i + m];
    }
}

int main() {
    string log = "vendor123 vendor123 login";
    string pattern = "vendor123";

    rabinKarp(log, pattern);
}

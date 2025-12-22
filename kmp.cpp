#include <iostream>
#include <string>
using namespace std;

/*
PROBLEM:
We want to detect suspicious IDs in system logs efficiently.
Each ID has a structured format like "accessID_987".
Logs can be very large, so we need an efficient string search algorithm.

SOLUTION:
Use KMP (Knuth-Morris-Pratt) algorithm:
- Preprocess the pattern to build LPS (Longest Prefix Suffix) table
- Slide pattern over text using LPS to skip unnecessary comparisons
- Time complexity: O(n + m), where n = text length, m = pattern length

WHY KMP:
Naive search may re-check characters repeatedly. KMP avoids this by using LPS,
making it perfect for large logs and multiple pattern searches.
*/

// Build LPS array for KMP
void buildLPS(string pat, int lps[]) {
    int len = 0;
    lps[0] = 0;

    cout << "Building LPS for pattern: " << pat << endl;

    for (int i = 1; i < pat.length();) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            cout << "lps[" << i << "] = " << lps[i] << " (characters matched: " << len << ")" << endl;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                cout << "Mismatch: Backtrack len to " << len << endl;
            } else {
                lps[i] = 0;
                cout << "lps[" << i << "] = 0" << endl;
                i++;
            }
        }
    }

    cout << "LPS array construction complete.\n\n";
}

// Search pattern in text using KMP
void KMP(string text, string pat) {
    int lps[100];
    buildLPS(pat, lps);

    int i = 0, j = 0;
    int matchCount = 0;

    cout << "Searching for pattern \"" << pat << "\" in log text...\n\n";

    while (i < text.length()) {
        if (text[i] == pat[j]) {
            i++; j++;
        }

        if (j == pat.length()) {
            cout << "Match found at index " << i - j << endl;
            matchCount++;
            j = lps[j - 1]; // Continue searching for next matches
        } else if (i < text.length() && text[i] != pat[j]) {
            if (j != 0) {
                cout << "Mismatch at text[" << i << "] and pattern[" << j << "], jump to lps[" << j-1 << "] = " << lps[j-1] << endl;
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    cout << "\nTotal matches found: " << matchCount << "\n\n";
}

// Function to search multiple suspicious IDs in logs
void searchMultipleIDs(string text, string patterns[], int nPatterns) {
    cout << "=== Multi-ID Suspicious Search ===\n\n";
    for (int k = 0; k < nPatterns; k++) {
        cout << "Searching for suspicious ID: " << patterns[k] << endl;
        KMP(text, patterns[k]);
        cout << "-------------------------------------\n";
    }
}

int main() {
    string logText = "accessID_987 accessID_123 accessID_987 accessID_999 accessID_123 accessID_987";
    string suspiciousIDs[3] = {"accessID_987", "accessID_123", "accessID_999"};

    cout << "System log analysis started...\n\n";
    searchMultipleIDs(logText, suspiciousIDs, 3);
    cout << "System log analysis completed.\n";

    return 0;
}

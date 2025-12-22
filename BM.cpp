#include <iostream>
#include <string>
using namespace std;

/*
PROBLEM STATEMENT:
This program searches for a rare malware signature inside large system log data.
Such signatures are difficult to detect using naive string matching methods.

WHY BOYER–MOORE:
Boyer–Moore algorithm reduces unnecessary comparisons by skipping characters
based on mismatch information, making it suitable for large log files.
*/

// Build bad character shift table
void prepareShiftTable(const string &pattern, int shift[]) {
    int length = pattern.length();

    for (int i = 0; i < 256; i++) {
        shift[i] = length;
    }

    for (int i = 0; i < length - 1; i++) {
        shift[pattern[i]] = length - 1 - i;
    }
}

// Check if pattern matches at given index
bool isPatternMatching(const string &text,
                       const string &pattern,
                       int startIndex) {
    int j = pattern.length() - 1;

    while (j >= 0) {
        if (text[startIndex + j] != pattern[j]) {
            return false;
        }
        j--;
    }
    return true;
}

// Boyer–Moore search implementation
void boyerMooreSearch(const string &text, const string &pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();

    int shift[256];
    prepareShiftTable(pattern, shift);

    int index = 0;

    while (index <= textLength - patternLength) {

        int j = patternLength - 1;

        while (j >= 0 &&
               pattern[j] == text[index + j]) {
            j--;
        }

        if (j < 0) {
            cout << "Malicious signature found at index "
                 << index << endl;

            char nextChar = text[index + patternLength - 1];
            index += shift[nextChar];
        }
        else {
            char badChar = text[index + j];
            index += shift[badChar];
        }
    }
}

// Wrapper function for malware scan
void detectMalware() {
    string logData = "safe_log MALWARE safe";
    string malwareSignature = "MALWARE";

    boyerMooreSearch(logData, malwareSignature);
}

int main() {
    detectMalware();
    return 0;
}

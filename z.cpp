#include <iostream>
#include <string>
using namespace std;

/*
    Z-Algorithm for String Matching
    --------------------------------
    - Detects exact occurrences of a pattern in a larger text
    - Useful for finding cloned or templated requests in logs
    - Runs in O(n + m) time
*/

void computeZArray(const string &concat, int Z[], int n) {
    int L = 0, R = 0;
    cout << "\nStarting Z-array computation for concatenated string: \"" << concat << "\"\n";

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && concat[R] == concat[R - L])
                R++;
            Z[i] = R - L;
            R--;
        } else {
            int k = i - L;
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];
            else {
                L = i;
                while (R < n && concat[R] == concat[R - L])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }

        cout << "i = " << i << " | L = " << L << " | R = " << R << " | Z[i] = " << Z[i] << endl;
    }
}

void ZalgoSearch(const string &text, const string &pattern) {
    string concat = pattern + "$" + text;
    int n = concat.length();
    int Z[200] = {0};  // initialize Z-array

    computeZArray(concat, Z, n);

    cout << "\nScanning for cloned requests in text...\n";
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (Z[i] == pattern.length()) {
            cout << "Cloned request detected at index " << i - pattern.length() - 1 << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No cloned requests detected in the given log.\n";

    cout << "\nFinal Z-array:\n";
    for (int i = 0; i < n; i++)
        cout << Z[i] << " ";
    cout << "\n";
}

int main() {
    cout << "===== Cloned Request Detection Using Z-Algorithm =====\n";

    string logText;
    string pattern;

    cout << "Enter the governance log text: ";
    getline(cin, logText);

    cout << "Enter the request pattern to search: ";
    getline(cin, pattern);

    cout << "\nSearching for cloned requests...\n";
    ZalgoSearch(logText, pattern);

    cout << "\n===== Search Complete =====\n";
    return 0;
}

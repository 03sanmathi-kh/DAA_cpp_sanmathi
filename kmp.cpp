#include <iostream>
#include <string>
using namespace std;

// Builds prefix table for structured ID matching
void buildLPS(string pat, int lps[]) {
    int len = 0;
    lps[0] = 0;

    for (int i = 1; i < pat.length();) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else if (len != 0)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
}

// Finds exact suspicious signature in logs
void KMP(string text, string pat) {
    int lps[100];
    buildLPS(pat, lps);

    int i = 0, j = 0;
    while (i < text.length()) {
        if (text[i] == pat[j]) {
            i++; j++;
        }

        if (j == pat.length()) {
            cout << "Suspicious ID found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < text.length() && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

int main() {
    KMP("accessID_987 accessID_987", "accessID_987");
}

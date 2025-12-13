#include <iostream>
#include <string>
using namespace std;

// Searches rare malware patterns in logs
void boyerMoore(string text, string pat) {
    int n = text.length(), m = pat.length();
    int shift[256];

    for (int i = 0; i < 256; i++)
        shift[i] = m;

    for (int i = 0; i < m - 1; i++)
        shift[pat[i]] = m - 1 - i;

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;

        while (j >= 0 && pat[j] == text[i + j])
            j--;

        if (j < 0) {
            cout << "Malicious signature found at index " << i << endl;
            i += shift[text[i + m - 1]];
        } else {
            i += shift[text[i + j]];
        }
    }
}

int main() {
    boyerMoore("safe_log MALWARE safe", "MALWARE");
}

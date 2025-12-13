#include <iostream>
#include <string>
using namespace std;

// Z-Algorithm is used here to explore a new string matching approach
// for detecting cloned or templated requests in governance logs
void Zalgo(string s, string pattern) {
    string concat = pattern + "$" + s;
    int n = concat.length();
    int Z[200] = {0};

    int L = 0, R = 0;
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

        // Pattern similarity found
        if (Z[i] == pattern.length())
            cout << "Cloned request detected at index " << i - pattern.length() - 1 << endl;
    }
}

int main() {
    Zalgo("REQ_LOGIN REQ_LOGIN", "REQ_LOGIN");
}

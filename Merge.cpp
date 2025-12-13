#include <iostream>
using namespace std;

// This function merges two already sorted eco-corridor lists
// so that corridors with less eco-strain come first
void merge(int a[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int temp[100]; // temporary storage for sorted eco-corridors

    // Compare eco-strain of corridors and arrange them
    while (i <= m && j <= r) {
        if (a[i] < a[j])        // lower eco-strain gets priority
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    // Copy remaining corridors from left side
    while (i <= m)
        temp[k++] = a[i++];

    // Copy remaining corridors from right side
    while (j <= r)
        temp[k++] = a[j++];

    // Copy sorted eco-corridors back to original array
    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];
}

// Merge Sort divides eco-corridors into smaller parts,
// sorts them and combines them back safely
void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        // Sort left eco-corridors
        mergeSort(a, l, m);

        // Sort right eco-corridors
        mergeSort(a, m + 1, r);

        // Merge sorted corridors
        merge(a, l, m, r);
    }
}

int main() {
    int n, ecoStrain[100];

    // Input number of eco-corridors
    cin >> n;

    // Input eco-strain value of each corridor
    for (int i = 0; i < n; i++)
        cin >> ecoStrain[i];

    // Sort corridors by eco-strain (least sensitive first)
    mergeSort(ecoStrain, 0, n - 1);

    // Display sorted eco-corridors
    for (int i = 0; i < n; i++)
        cout << ecoStrain[i] << " ";
}

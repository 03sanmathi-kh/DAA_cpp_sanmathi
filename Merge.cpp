#include <iostream>
using namespace std;

/*
PROBLEM STATEMENT:
Eco-corridors have different eco-strain values.
The goal is to sort corridors so that less sensitive
corridors (lower eco-strain) appear first.

WHY MERGE SORT:
Merge Sort efficiently sorts large datasets using divide-and-conquer.
It guarantees O(n log n) performance and is stable.
*/

// Merge two sorted parts of eco-strain array
void merge(int ecoStrain[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[100], rightArr[100];

    for (int i = 0; i < n1; i++)
        leftArr[i] = ecoStrain[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = ecoStrain[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            ecoStrain[k++] = leftArr[i++];
        } else {
            ecoStrain[k++] = rightArr[j++];
        }
    }

    while (i < n1)
        ecoStrain[k++] = leftArr[i++];
    while (j < n2)
        ecoStrain[k++] = rightArr[j++];
}

// Recursive merge sort
void mergeSort(int ecoStrain[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(ecoStrain, left, mid);
        mergeSort(ecoStrain, mid + 1, right);
        merge(ecoStrain, left, mid, right);
    }
}

// Read eco-strain values from input
void readEcoStrainValues(int ecoStrain[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> ecoStrain[i];
    }
}

// Display eco-strain array
void displayEcoStrain(int ecoStrain[], int n) {
    cout << "Sorted eco-strains: ";
    for (int i = 0; i < n; i++) {
        cout << ecoStrain[i] << " ";
    }
    cout << endl;
}

// Optional check for negative eco-strain values
bool validateEcoStrain(int ecoStrain[], int n) {
    bool valid = true;
    for (int i = 0; i < n; i++) {
        if (ecoStrain[i] < 0) {
            cout << "Warning: Negative eco-strain at position " << i << endl;
            valid = false;
        }
    }
    return valid;
}

// Controller function for sorting eco-corridors
void sortEcoCorridors() {
    int n, ecoStrain[100];

    cin >> n;
    readEcoStrainValues(ecoStrain, n);

    validateEcoStrain(ecoStrain, n);

    mergeSort(ecoStrain, 0, n - 1);

    displayEcoStrain(ecoStrain, n);
}



int main() {
    sortEcoCorridors();
    return 0;
}

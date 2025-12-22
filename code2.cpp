#include <iostream>
#include <string>
using namespace std;

// Structure to store candidate information
struct Candidate {
    string name;
    bool isLocal;       // true if Vishalnagari student
    int experience;
    int academicScore;
    int certifications;
};

// Function to swap two candidates
void swap(Candidate &a, Candidate &b) {
    Candidate temp = a;
    a = b;
    b = temp;
}

// Function to heapify a subtree rooted at index i (for max-heap)
void heapify(Candidate arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2*i + 1;
    int right = 2*i + 2;

    auto compare = [](Candidate a, Candidate b) {
        if (a.isLocal != b.isLocal)
            return a.isLocal < b.isLocal; // local first
        if (a.experience != b.experience)
            return a.experience < b.experience;
        if (a.academicScore != b.academicScore)
            return a.academicScore < b.academicScore;
        return a.certifications < b.certifications;
    };

    if (left < n && compare(arr[largest], arr[left]))
        largest = left;
    if (right < n && compare(arr[largest], arr[right]))
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build max-heap
void buildHeap(Candidate arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to perform heap sort (extract candidates in order)
void heapSort(Candidate arr[], int n) {
    buildHeap(arr, n);
    for (int i = n-1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    // Step 1: Create candidates array
    Candidate candidates[5] = {
        {"Shreya", true, 3, 88, 2},
        {"Dhanya", false, 5, 90, 1},
        {"Megha", true, 2, 80, 3},
        {"Yashaswini", false, 4, 70, 2},
        {"Poorvi", true, 4, 95, 1}
    };

    int n = 5;

    // Step 2: Sort candidates using heap sort based on priority
    heapSort(candidates, n);

    // Step 3: Print candidates in priority order (local first, etc.)
    cout << "Selected candidates for the job:" << endl;
    for (int i = n-1; i >= 0; i--) { // heapSort gives ascending, so print from end
        cout << candidates[i].name
             << " | Local: " << (candidates[i].isLocal ? "Yes" : "No")
             << " | Exp: " << candidates[i].experience
             << " | Score: " << candidates[i].academicScore
             << " | Certs: " << candidates[i].certifications << endl;
    }

    return 0;
}

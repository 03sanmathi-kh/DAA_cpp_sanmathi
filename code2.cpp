#include <iostream>
#include <string>
using namespace std;

/*
PROBLEM:
Select candidates for a job based on priority:
1. Local students (Vishalnagari) get preference
2. More experience is better
3. Higher academic score is better
4. More certifications are better

WHY HEAP SORT:
Heap sort allows efficient selection of candidates in priority order.
Using a max-heap, we can always extract the candidate with the highest
priority and sort them in decreasing priority order.
*/

// Structure to store candidate information
struct Candidate {
    string name;
    bool isLocal;       // true if Vishalnagari student
    int experience;
    int academicScore;
    int certifications;
};

// Compare two candidates; returns true if a has lower priority than b
bool compareCandidates(const Candidate &a, const Candidate &b) {
    if(a.isLocal != b.isLocal)
        return a.isLocal < b.isLocal; // local first
    if(a.experience != b.experience)
        return a.experience < b.experience;
    if(a.academicScore != b.academicScore)
        return a.academicScore < b.academicScore;
    return a.certifications < b.certifications;
}

// Swap two candidates
void swapCandidates(Candidate &a, Candidate &b) {
    Candidate temp = a;
    a = b;
    b = temp;
}

// Heapify a subtree rooted at index i
void heapify(Candidate arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && compareCandidates(arr[largest], arr[left]))
        largest = left;
    if(right < n && compareCandidates(arr[largest], arr[right]))
        largest = right;

    if(largest != i) {
        swapCandidates(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Build max-heap
void buildHeap(Candidate arr[], int n) {
    for(int i=n/2-1; i>=0; i--) {
        heapify(arr, n, i);
    }
}

// Heap sort
void heapSort(Candidate arr[], int n) {
    buildHeap(arr, n);

    cout << "\nHeap after building max-heap:\n";
    for(int i=0;i<n;i++)
        cout << arr[i].name << " ";
    cout << "\n\n";

    for(int i=n-1; i>=0; i--) {
        swapCandidates(arr[0], arr[i]);
        heapify(arr, i, 0);

        // Print heap after each extraction
        cout << "Heap after extracting " << arr[i].name << ":\n";
        for(int j=0;j<i;j++)
            cout << arr[j].name << " ";
        cout << "\n";
    }
}

// Display candidate information
void displayCandidates(Candidate arr[], int n) {
    cout << "\nSelected candidates in priority order:\n";
    for(int i=n-1;i>=0;i--) { // heapSort gives ascending, so print from end
        cout << arr[i].name
             << " | Local: " << (arr[i].isLocal ? "Yes" : "No")
             << " | Exp: " << arr[i].experience
             << " | Score: " << arr[i].academicScore
             << " | Certs: " << arr[i].certifications << endl;
    }
}

// Optional: read candidates from user
void readCandidates(Candidate arr[], int n) {
    for(int i=0;i<n;i++) {
        cout << "Enter details for candidate " << i+1 << ":\n";
        cout << "Name: "; cin >> arr[i].name;
        cout << "Local (1=yes,0=no): "; cin >> arr[i].isLocal;
        cout << "Experience (years): "; cin >> arr[i].experience;
        cout << "Academic Score: "; cin >> arr[i].academicScore;
        cout << "Certifications: "; cin >> arr[i].certifications;
        cout << "\n";
    }
}

int main() {
    int n = 5;

    // Step 1: Initialize candidates
    Candidate candidates[5] = {
        {"Shreya", true, 3, 88, 2},
        {"Dhanya", false, 5, 90, 1},
        {"Megha", true, 2, 80, 3},
        {"Yashaswini", false, 4, 70, 2},
        {"Poorvi", true, 4, 95, 1}
    };

    // Optional: uncomment to read from user
    // readCandidates(candidates, n);

    // Step 2: Sort candidates using heap sort
    heapSort(candidates, n);

    // Step 3: Display sorted candidates
    displayCandidates(candidates, n);

    return 0;
}

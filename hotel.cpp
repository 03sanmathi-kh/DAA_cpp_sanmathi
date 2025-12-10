#include <iostream>
#include <string>
using namespace std;


//  Segment Tree for minimum crowd queries

class SegmentTree {
    int* tree;  // array to store the segment tree nodes
    int n;      // size of original data

    // Build the segment tree recursively
    void build(int a[], int v, int tl, int tr) {
        if (tl == tr)
            tree[v] = a[tl]; // leaf node stores single day's crowd
        else {
            int tm = (tl + tr) / 2;
            build(a, 2*v, tl, tm);         // build left child
            build(a, 2*v+1, tm+1, tr);     // build right child
            tree[v] = min(tree[2*v], tree[2*v+1]); // parent stores min of children
        }
    }

    // Query the minimum crowd in range [l, r]
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 1e9;            // invalid range returns "infinity"
        if (l == tl && r == tr) return tree[v]; // exact match
        int tm = (tl + tr) / 2;
        // Query left and right child and take minimum
        return min(query(2*v, tl, tm, l, min(r, tm)),
                   query(2*v+1, tm+1, tr, max(l, tm+1), r));
    }


    //  builds tree from input array
    SegmentTree(int a[], int size) {
        n = size;
        tree = new int[4*n]; // allocate enough space for tree
        build(a, 1, 0, n-1);
    }

    // Public function to query minimum crowd in range [l, r]
    int rangeMin(int l, int r) { 
        return query(1, 0, n-1, l, r); 
    }

    ~SegmentTree() {
        delete[] tree; // free allocated memory
    }
};


// Linked List Node for Events

struct EventNode {
    int day;           // day index
    string name;       // event name
    EventNode* next;   // pointer to next event
    EventNode(int d, string n) { day = d; name = n; next = nullptr; }
};

// ========================
// Main Function
// ========================
int main() {
    // Array of crowd data for each day
    int crowd[] = {5, 10, 7, 12, 6, 8, 15};
    int n = sizeof(crowd)/sizeof(crowd[0]);

    // Initialize linked list for events
    EventNode* events = new EventNode(0, "New Year");
    events->next = new EventNode(3, "Festival");
    events->next->next = new EventNode(6, "Vacation");

    // Initialize segment tree with crowd data
    SegmentTree st(crowd, n);

    int bestDay = -1;      // variable to store recommended day
    int minCrowd = 1e9;    // initialize with a very large number

    cout << "Day-wise crowd and events:\n";

    // Iterate over each day
    for (int i = 0; i < n; i++) {
        cout << "Day " << i << " - Crowd: " << crowd[i];

        // Iterate linked list to check if an event exists for this day
        EventNode* current = events;
        while (current != nullptr) {
            if (current->day == i) cout << " | Event: " << current->name;
            current = current->next;
        }

        cout << endl;

        // Update best day if current day has lower crowd
        if (crowd[i] < minCrowd) {
            minCrowd = crowd[i];
            bestDay = i;
        }
    }

    // Output recommended day based on minimum crowd
    cout << "\nRecommended day to visit: Day " << bestDay 
         << " with crowd " << minCrowd << endl;

    // Free linked list memory
    EventNode* temp;
    while (events != nullptr) {
        temp = events;
        events = events->next;
        delete temp;
    }

    return 0;
}

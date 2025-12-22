#include <iostream>
#include <vector>
using namespace std;

/*
TOURIST MONITORING DASHBOARD:
I planned to maintain live counts of tourists in multiple zones using a Fenwick Tree (BIT).

Operations:
1. update(idx, val)   -> Add val tourists at a zone (entry/exit)
2. sum(idx)           -> Total tourists from zone 1 to idx
3. rangeSum(l, r)     -> Total tourists from zone l to r

WHY FENWICK TREE:
Both update and query take O(log n), making it perfect for real-time updates
in dashboards with many zones and frequent tourist movements.
*/


class Fenwick {
    vector<int> bit;
    int n;

public:
    Fenwick(int size) {
        n = size;
        bit.assign(n+1, 0);
        cout << "Initialized Fenwick Tree with " << n << " zones.\n\n";
    }

    // Add val tourists at zone idx
    void update(int idx, int val) {
        cout << "Updating Zone " << idx << " by " << val << " tourists.\n";
        while(idx <= n){
            bit[idx] += val;
            cout << "  -> BIT[" << idx << "] now = " << bit[idx] << "\n";
            idx += idx & -idx;
        }
        cout << "Update completed.\n\n";
    }

    // Prefix sum from zone 1 to idx
    int sum(int idx){
        int s = 0;
        while(idx > 0){
            s += bit[idx];
            idx -= idx & -idx;
        }
        return s;
    }

    // Total tourists between zone l and r
    int rangeSum(int l, int r){
        cout << "Querying tourists from Zone " << l << " to Zone " << r << "...\n";
        int result = sum(r) - sum(l-1);
        cout << "  -> Total tourists = " << result << "\n\n";
        return result;
    }

    // Display BIT internal state
    void displayBIT(){
        cout << "Current Fenwick Tree state:\n";
        for(int i=1;i<=n;i++)
            cout << bit[i] << " ";
        cout << "\n\n";
    }
};

/* ----------------------------
   Simulate Live Tourist Movements
   ---------------------------- */
void simulateTouristEvents(Fenwick &ft){
    cout << "--- Simulating Tourist Entries ---\n\n";

    ft.update(2, 10);  // 10 tourists entered zone 2
    ft.update(3, 15);  // 15 tourists entered zone 3
    ft.update(5, 20);  // 20 tourists entered zone 5
    ft.update(7, 8);   // 8 tourists entered zone 7
    ft.update(3, 5);   // additional 5 entered zone 3
    ft.update(1, 12);  // 12 entered zone 1
    ft.update(6, 18);  // 18 entered zone 6
    ft.update(10, 25); // 25 entered zone 10

    cout << "--- All Updates Completed ---\n\n";
    ft.displayBIT();
}

/* ----------------------------
   Perform Range Queries
   ---------------------------- */
void performQueries(Fenwick &ft){
    cout << "--- Performing Range Queries ---\n\n";
    ft.rangeSum(1, 5);
    ft.rangeSum(3, 7);
    ft.rangeSum(2, 10);
    ft.rangeSum(1, 10);
    ft.rangeSum(6, 10);
}

/* ----------------------------
   Main Controller
   ---------------------------- */
void runTouristMonitoring(){
    int zones = 10;
    Fenwick ft(zones);

    simulateTouristEvents(ft);
    performQueries(ft);

    // Additional step: live dashboard simulation
    cout << "--- Live Dashboard Simulation ---\n\n";

    vector<pair<int,int>> liveEvents = {
        {4, 10}, {2, -3}, {7, 5}, {9, 12}, {1, -2}, {5, 8}
    };

    for(auto event : liveEvents){
        int zone = event.first;
        int change = event.second;
        if(change>0)
            cout << "New tourists entered Zone " << zone << ": " << change << "\n";
        else
            cout << "Tourists exited Zone " << zone << ": " << -change << "\n";

        ft.update(zone, change);
        ft.displayBIT();
    }

    cout << "--- Final Dashboard ---\n";
    for(int i=1;i<=zones;i++){
        int count = ft.rangeSum(i,i);
        cout << "Zone " << i << " has " << count << " tourists.\n";
    }
}


int main(){
    cout << "=== Real-Time Tourist Monitoring using Fenwick Tree ===\n\n";
    runTouristMonitoring();
    return 0;
}

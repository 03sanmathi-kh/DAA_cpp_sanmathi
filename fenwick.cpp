#include <iostream>
using namespace std;

/*
   
   I used to maintain real-time tourist counts in multiple zones.
   - update(idx, val): Add tourists in a specific zone (entry/exit)
   - sum(idx): Total tourists from zone 1 to idx
   - rangeSum(l, r): Tourists between zone l and r
   Why Fenwick? Because both update and query take O(log n),
   making it perfect for live dashboards.
*/

class Fenwick {
    int bit[100], n;

public:
    Fenwick(int size) {
        n = size;
        for (int i = 0; i <= n; i++) bit[i] = 0;
    }

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int sum(int idx) {
        int s = 0;
        while (idx > 0) {
            s += bit[idx];
            idx -= idx & -idx;
        }
        return s;
    }

    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    Fenwick ft(10);

    // Live tourist arrivals in some zones
    ft.update(3, 12);  // 12 entered zone 3
    ft.update(5, 8);   // 8 entered zone 5
    ft.update(7, 20);  // 20 entered zone 7

    cout << "Tourists from Zone 1 to 7 = "
         << ft.rangeSum(1, 7) << endl;

    return 0;
}

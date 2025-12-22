#include <iostream>
#include <vector>
using namespace std;

/*
PROBLEM:
Monitor AQI values in a school area. If the average AQI over a recent
time window exceeds a safe limit, generate an alert for students and staff.

WHY SLIDING WINDOW:
The sliding window allows efficient computation of averages over
consecutive intervals without recalculating sums from scratch.
*/


const int SAFE_AQI = 100; // Safe AQI limit

// Compute average of current window
int computeAverage(int sum, int size) {
    return sum / size;
}

// Check if average AQI exceeds safe limit
bool checkAQIAlert(int avg) {
    return avg > SAFE_AQI;
}

// Display AQI alert message
void displayAlert(int avg) {
    if(checkAQIAlert(avg)) {
        cout << "ALERT: Unhealthy AQI detected! "
             << "Students should limit outdoor activities.\n\n";
    } else {
        cout << "AQI is safe for students.\n\n";
    }
}

// Monitor AQI readings using sliding window
void monitorAQI(const vector<int> &aqiData, int windowSize) {
    int windowSum = 0;

    // Initialize the first window
    for(int i=0; i<windowSize; i++)
        windowSum += aqiData[i];

    // Sliding window processing
    for(int i = windowSize; i <= aqiData.size(); i++) {
        int avgAQI = computeAverage(windowSum, windowSize);
        cout << "Average AQI (last " << windowSize << " hours): " << avgAQI << endl;

        displayAlert(avgAQI);

        // Slide the window
        if(i < aqiData.size()) {
            windowSum -= aqiData[i - windowSize];
            windowSum += aqiData[i];
        }
    }
}

// Read AQI data from user
vector<int> readAQIData(int n) {
    vector<int> data(n);
    cout << "Enter " << n << " AQI readings (hourly):\n";
    for(int i=0; i<n; i++)
        cin >> data[i];
    return data;
}

// Controller function
void runAQIMonitoring() {
    int n, windowSize;

    cout << "Enter number of AQI readings: ";
    cin >> n;

    vector<int> aqiData = readAQIData(n);

    cout << "Enter sliding window size: ";
    cin >> windowSize;

    cout << "\nMonitoring AQI levels...\n\n";
    monitorAQI(aqiData, windowSize);
}

int main() {
    runAQIMonitoring();
    return 0;
}

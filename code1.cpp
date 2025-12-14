#include <iostream>
#include <vector>
using namespace std;

/*
 Problem:
 Monitor AQI values over time in a school area.
 If the average AQI over a recent time window exceeds a safe limit,
 generate an alert for students and staff.
*/

// Safe AQI limit for students
const int SAFE_AQI = 100;

int main() {

    // Sample AQI readings collected hourly
    vector<int> aqiData = {72, 85, 90, 110, 130, 125, 95, 80};

    int windowSize = 3;   // Sliding window size (last 3 hours)
    int windowSum = 0;

    cout << "Monitoring AQI levels...\n\n";

    // Initialize the first window
    for (int i = 0; i < windowSize; i++) {
        windowSum += aqiData[i];
    }

    // Check AQI using Sliding Window
    for (int i = windowSize; i <= aqiData.size(); i++) {

        // Compute average AQI of current window
        int avgAQI = windowSum / windowSize;

        cout << "Average AQI (last " << windowSize 
             << " hours): " << avgAQI << endl;

        // Alert if AQI is unsafe
        if (avgAQI > SAFE_AQI) {
            cout << "ALERT: Unhealthy AQI detected! "
                 << "Students should limit outdoor activities.\n\n";
        } else {
            cout <<  AQI is safe for students.\n\n";
        }

        // Slide the window
        if (i < aqiData.size()) {
            windowSum -= aqiData[i - windowSize]; // remove old AQI
            windowSum += aqiData[i];               // add new AQI
        }
    }

    return 0;
}

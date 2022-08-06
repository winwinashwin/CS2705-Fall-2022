/**
 * @file     A00_Q02_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int find_missing(vector<int> &arr) {
    int repeating, missing;

    // Find repeating element
    for (int i = 0; i < arr.size(); ++i) {
        // Use absolute value of element as index
        int idx = abs(arr[i]) - 1;
        if (arr[idx] < 0) {
            // If we encounter a negative value, we know it was visited before
            repeating = idx + 1;
        }
        // Mark element at index as negative, denoting it was visited
        arr[idx] *= -1;
    }

    // Find first positive element in array, returns pointer to element
    auto pos = find_if(arr.begin(), arr.end(), [](int n){ return n > 0; });
    // Compute index and consequently the missing value
    missing = (pos - arr.begin()) + 1;

    return missing;
}

int main(int argc, char **argv) {
    int n;
    string line;
    vector<int> arr;

    getline(cin, line);
    istringstream ss(line);

    while (ss >> n) {
        arr.push_back(n);
    }

    int missing = find_missing(arr);
    
    cout << missing << endl;

    return EXIT_SUCCESS;
}

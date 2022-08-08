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
    int n = arr.size();
    int sum_expected = (n+1)*(n+2)/2;
    int sum_actual = 0;

    for (int v : arr) sum_actual += v;

    return sum_expected - sum_actual;
}

int main(int argc, char **argv) {
    int n; cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    int missing = find_missing(arr);

    cout << missing << endl;

    return EXIT_SUCCESS;
}

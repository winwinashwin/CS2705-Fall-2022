/**
 * @file     A00_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

int sub_arrays_d5(const vector<int> &arr) {
    int res = 0;
    int prev_idx = -1;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] % 5 == 0) {
            res += (i-prev_idx)*(arr.size() - i);
            prev_idx = i;
        }
    }
    return res;
}

int main(int argc, char **argv) {
    // Read input
    int n; cin >> n;
    vector<int> arr(n);
    for (auto &v: arr) cin >> v;

    cout << sub_arrays_d5(arr) << endl;

    return EXIT_SUCCESS;
}

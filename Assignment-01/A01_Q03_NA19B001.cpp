/**
 * @file     A01_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    int n1, n2;
    cin >> n1 >> n2;

    vector<int> arr1(n1), arr2(n2);
    for (auto& e : arr1) cin >> e;
    for (auto& e : arr2) cin >> e;

    int i = 0, j = 0;
    int mid1 = 0, mid2 = 0;

    for (int k = 0; k <= (n1 + n2)/2; ++k) {
        mid2 = mid1;
        if (i != n1 && j != n2) {
            mid1 = arr1[i] < arr2[j] ? arr1[i++] : arr2[j++];
        } else if (i < n1) {
            mid1 = arr1[i++];
        } else {
            mid1 = arr2[j++];
        }
    }

    double median;
    if ((n1 + n2)&1) {
        median = mid1;
    } else {
        median = (double)(mid1 + mid2)/2.0;
    }

    printf("%.2lf\n", median);

    return EXIT_SUCCESS;
}

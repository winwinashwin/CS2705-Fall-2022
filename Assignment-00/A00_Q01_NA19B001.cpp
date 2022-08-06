/**
 * @file     A00_Q01_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int computeFib(int n) {
    if (n==0) return 0;
    if (n==1) return 1;

    return computeFib(n-1) + computeFib(n-2);
}

int smartFib(int n) {
    static vector<int> fibstore = {0, 1};

    if (n < fibstore.size()) return fibstore[n];

    int fibn = smartFib(n-1) + smartFib(n-2);
    fibstore.push_back(fibn);

    return fibn;
}

int main(int argc, char **argv) {
    // Read Input
    int n; cin >> n;

    using namespace std::chrono;

    // Outputs from each implementation 
    int fibn_rec, fibn_smart;
    // Execution time for each implementation
    duration<long> duration_rec, duration_smart;

    // Measure execution time for `computeFib`
    {
        auto start = high_resolution_clock::now();
        fibn_rec = computeFib(n);
        auto stop = high_resolution_clock::now();
        duration_rec = duration_cast<seconds>(stop - start);
    }

    // Measure execution time for `smartFib`
    {
        auto start = high_resolution_clock::now();
        fibn_smart = smartFib(n);
        auto stop = high_resolution_clock::now();
        duration_smart = duration_cast<seconds>(stop - start);
    }
    
    // Output
    cout << fibn_smart << " "
         << duration_rec.count() << " "
         << duration_smart.count() << " "
         << endl;

    return EXIT_SUCCESS;
}


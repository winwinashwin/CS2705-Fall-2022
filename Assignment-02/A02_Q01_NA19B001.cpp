/**
 * @file     A02_Q01_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// Stores level-order traversal of binary tree in array form.
// For any index i,
//   - left child of i will be at 2*i+1
//   - right child of i will be at 2*i+2
//   - parent of i will be at (i-1)>>1
vector<ll> btree;

/**
 * Returns index of left child if present, else -1
 */
int get_left_child(int i) {
    int idx = 2*i + 1;
    if (idx >= btree.size()) return -1;
    else return idx;
}

/**
 * Returns index of right child if present, else -1
 */
int get_right_child(int i) {
    int idx = 2*i + 2;
    if (idx >= btree.size()) return -1;
    else return idx;
}

int main(int argc, char **argv) {
    int n; cin >> n;
    int read = 0; // number of valid nodes (value != -1) read so far
    while (1) {
        if (read == n) break;

        ll x; cin >> x;
        btree.push_back(x);
        if (x != -1) read++; 
    }
    ll target; cin >> target;

    int ans = 0;

    // The idea is to find the sum of nodes in the unique path from leaf->root for all
    // leaf nodes in the binary tree and compare the sum with the target sum required

    for (int i = btree.size()-1; i >= 0; --i) {
        // Skip null nodes
        if (btree[i] == -1) continue;
        int ileft = get_left_child(i);
        int iright = get_right_child(i);
        // If node has valid left child, not a leaf node. Skip.
        if (ileft != -1 && btree[ileft] != -1) continue;
        // If node has valid right child, not a leaf node. Skip.
        if (iright != -1 && btree[iright] != -1) continue;

        ll sm = 0;
        int iparent = i;
        while (iparent) {
            sm += btree[iparent];
            if (sm > target) break;
            iparent = (iparent-1)>>1;
        }
        // Sum value at root
        sm += btree[iparent];
        if (sm == target) ans++;
    }

    cout << ans << endl;

    return EXIT_SUCCESS;
}


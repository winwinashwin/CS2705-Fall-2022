/**
 * @file     A02_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

// We represent level order traversal of binary trees in array form
// - Index of left child of i = 2*i + 1
// - Index of right child of i = 2*i + 2
// - Index of parent of i = (i-1)>>1

vector<int> btree;      // Stores input tree
vector<int> btree_sum;  // Element at index `i` stores sum of subtree with root `btree[i]`

// Compute index of left child
int get_left_child(int i) {
    int idx = 2*i + 1;
    if (idx >= btree.size()) return -1;
    return idx;
} 

// Check if node `i` has valid left child
bool has_left(int i) {
    int ileft = get_left_child(i);
    return (ileft != -1 && btree[ileft] != -1);
}

// Compute index of right child
int get_right_child(int i) {
    int idx = 2*i + 2;
    if (idx >= btree.size()) return -1;
    return idx;
}

// Check if node `i` has valid right child
bool has_right(int i) {
    int iright = get_right_child(i);
    return (iright != -1 && btree[iright] != -1);
}

// Recursive function to generate modified binary tree
void modify_tree(int iroot, bool is_right = false) {
    /**
     * We follow a postorder processing scheme so that the modification happens in a
     * bottom-up fashion
     */
    if (has_left(iroot)) modify_tree(get_left_child(iroot));
    if (has_right(iroot)) modify_tree(get_right_child(iroot), true);

    // Update subtree sum
    btree_sum[iroot] = btree[iroot];
    if (has_left(iroot)) btree_sum[iroot] += btree_sum[get_left_child(iroot)];
    if (has_right(iroot)) btree_sum[iroot] += btree_sum[get_right_child(iroot)];

    // Modify right nodes
    if (is_right) {
        int iparent = (iroot-1)>>1;
        btree[iroot] += btree[iparent];
        if (has_left(iparent)) {
            int iparent_left = get_left_child(iparent);
            btree[iroot] += btree_sum[iparent_left];
        }
    }
}

int main(int argc, char **argv) {
    int n; cin >> n;
    int x;
    while (cin >> x) {
        btree.push_back(x);
    }
    btree_sum.resize(btree.size(), 0);

    modify_tree(0);

    // Print modified tree without missing nodes
    for (int& v : btree) {
        if (v == -1) continue;
        cout << v << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}

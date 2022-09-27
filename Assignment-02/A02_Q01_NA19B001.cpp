/**
 * @file     A02_Q01_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

namespace BT {
    using data_t = long long;

    struct Node {
        data_t data;
        Node* left;
        Node* right;

        Node(data_t _data = 0LL) : data(_data), left(nullptr), right(nullptr) {}
    };

    /**
     * Build binary tree from level order traversal
     *
     * @param lot Level order traveral of binary tree
     * @return Pointer to root of binary tree
     */
    Node* build_tree(const vector<data_t> &lot) {
        vector<Node*> nodes(lot.size(), nullptr);

        for (int i = 0; i < nodes.size(); ++i) {
            if (lot[i] == -1) continue;
            nodes[i] = new BT::Node(lot[i]);
        }

        for (int i = 0; i < nodes.size(); ++i) {
            int ileft = 2*i+1;
            if (ileft < nodes.size() && nodes[ileft])
                nodes[i]->left = nodes[ileft];

            int iright = 2*i+2;
            if (iright < nodes.size() && nodes[iright])
                nodes[i]->right = nodes[iright];
        }

        return nodes[0];
    }
}  // BT

/**
 * Compute number of paths from root to leaf nodes whose sum is equal to target
 *
 * @param root Pointer to root of binary tree
 * @param[in] sum_so_far Path sum so far
 * @param target Target sum
 * @param[out] nways Number of paths whose sum equals target
 */
void solve(BT::Node* root, BT::data_t& sum_so_far, const BT::data_t& target, int &nways) {
    /*
     * Traverse in preorder fashion and keep on summing up node values until a
     * leaf node is encountered. At leaf node compare sum and update counter.
     * Backtrack and proceed to next leaf node.
     */

    // Update sum
    sum_so_far += root->data;

    // Check if current node is a leaf node
    if (!root->left && !root->right && sum_so_far == target) {
        // Update counter and backtrack
        nways++;
        sum_so_far -= root->data;
        return;
    }

    // Move to left subtree
    if (root->left) solve(root->left, sum_so_far, target, nways);
    // Move to right subtree
    if (root->right) solve(root->right, sum_so_far, target, nways);
    // Backtrack
    sum_so_far -= root->data;
}

int main() {
    int n; cin >> n;
    vector<BT::data_t> level_order;

    for(int read = 0; read != n; ) {
        BT::data_t x; cin >> x;
        level_order.push_back(x);
        if (x != -1) read++;
    }

    BT::data_t target; cin >> target;

    BT::Node* root = BT::build_tree(level_order);

    int nways = 0;
    BT::data_t sm = 0;
    solve(root, sm, target, nways);
    cout << nways << endl;
}

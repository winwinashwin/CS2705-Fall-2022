/**
 * @file     A02_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

namespace BT {
using data_t = long long;

struct Node {
  data_t data;  // Value at node
  data_t sum;   // Sum of subtree with this node as root
  Node *parent; // Parent node
  Node *left;
  Node *right;

  Node(data_t _data = 0LL)
      : data(_data), sum(_data), left(nullptr), right(nullptr),
        parent(nullptr) {}
};

/**
 * Build binary tree from level order traversal
 *
 * @param lot Level order traveral of binary tree
 * @param[out] nodes Stores pointers to all nodes in binary tree
 * @return Pointer to root of binary tree
 */
Node *build_tree(const vector<data_t> &lot, vector<Node *> &nodes) {
  nodes.resize(lot.size(), nullptr);

  for (int i = 0; i < nodes.size(); ++i) {
    if (lot[i] == -1)
      continue;
    nodes[i] = new BT::Node(lot[i]);
  }

  for (int i = 0; i < nodes.size(); ++i) {
    int ileft = 2 * i + 1;
    if (ileft < nodes.size() && nodes[ileft]) {
      nodes[i]->left = nodes[ileft];
      nodes[ileft]->parent = nodes[i];
    }

    int iright = 2 * i + 2;
    if (iright < nodes.size() && nodes[iright]) {
      nodes[i]->right = nodes[iright];
      nodes[iright]->parent = nodes[i];
    }
  }

  return nodes[0];
}
} // namespace BT

// Recursive function to generate modified binary tree
void modify_tree(BT::Node *root, bool is_right = false) {
  /**
   * We follow a postorder processing scheme so that the modification happens in
   * a bottom-up fashion
   */
  if (!root)
    return;

  modify_tree(root->left);
  modify_tree(root->right, true);

  // Update subtree sum
  if (root->left)
    root->sum += root->left->sum;
  if (root->right)
    root->sum += root->right->sum;

  // Modify right nodes
  if (is_right) {
    root->data += root->parent->data;
    if (root->parent->left) {
      root->data += root->parent->left->sum;
    }
  }
}

int main(int argc, char **argv) {
  int n;
  cin >> n;
  vector<BT::data_t> level_order;

  for (int read = 0; read != n;) {
    BT::data_t x;
    cin >> x;
    level_order.push_back(x);
    if (x != -1)
      read++;
  }

  vector<BT::Node *> nodes;
  BT::Node *root = BT::build_tree(level_order, nodes);

  modify_tree(root);

  // Print modified tree without missing nodes
  for (auto &node : nodes) {
    if (node)
      cout << node->data << " ";
  }
  cout << endl;

  return EXIT_SUCCESS;
}

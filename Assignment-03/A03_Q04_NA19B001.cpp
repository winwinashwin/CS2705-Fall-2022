/**
 * @file     A03_Q04_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * The Disjoint-Set-Union data structure
 */
class DSU {

    // Represents a LinkedList node
    struct Node {
        Node *parent, *next;
        size_t size;
    };

    public:
        // Constructor
        explicit DSU(size_t N) {
            _nodes.resize(N, nullptr);
            for (size_t i = 0; i < N; ++i) {
                make_set(i);
            }
        }

        // Destructor
        ~DSU() {
            for (size_t i = 0; i < _nodes.size(); ++i) {
                delete _nodes[i];
                _nodes[i] = nullptr;
            }
        }

        void make_set(size_t n) {
            auto node = new Node;
            node->parent = node;  // set parent to self
            node->next = nullptr;
            node->size = 1;
            _nodes[n] = node;
        }

        Node* find_set(size_t n) {
            return _nodes[n]->parent;
        }

        void union_sets(size_t a, size_t b) {
            Node* pa = find_set(a);  // Parent of a
            Node* pb = find_set(b);  // Parent of b

            if (pa == pb) return;  // Already in same set, abort

            if (pa->size < pb->size) {
                swap(pa, pb);
                swap(a,b);
            }

            // list with `a` is now the larger list

            Node *trail_a = _nodes[a]->next;  // Cut list at `a`
            _nodes[a]->next = pb;  // Join smaller set
            
            // Update parent pointers of smaller set to parent of larger set
            Node *curr = _nodes[a];
            while (curr->next) {
                curr->next->parent = pa;
                curr = curr->next;
            }

            // Join trailing list post `a` to end of smaller set
            curr->next = trail_a;

            // Update size of largest set
            pa->size += pb->size;
        }

    private:
        vector<Node*> _nodes;
};

int main(int argc, char **argv) {
    int n, k, c; cin >> n >> k >> c;

    DSU dsu(n);

    // Process specialists
    int specialist;  // will serve as representative among specialists
    cin >> specialist;
    while (--k) {
        int s; cin >> s;
        dsu.union_sets(s, specialist);
    }

    // Process queries
    string query;
    while (c--) {
        cin >> query;
        if (query == "is-expert") {
            int s; cin >> s;
            if (dsu.find_set(s) == dsu.find_set(specialist))
                puts("Yes");
            else
                puts("No");

        } else if (query == "new-paper") {
            int a, b; cin >> a >> b;
            dsu.union_sets(a,b);

        }
    }
    return EXIT_SUCCESS;
}


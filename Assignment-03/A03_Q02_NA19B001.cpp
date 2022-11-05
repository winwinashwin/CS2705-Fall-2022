/**
 * @file     A03_Q02_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    /**
     * Logic: Each node in the graph has atmost one outgoing edge, SCCs if present will be cycles
     *        in the graph. To find the largest SCC, We can iterate each subgraph keeping a level 
     *        array. On reaching a previously visited node, if in the same subgraph, we update the answer.
     *        Each node is visited once, hence O(n)
     */

    int n, m; cin >> n >> m;
    vector<int> edges(n, -1);  // Nodes have atmost one outgoing edge, -1 denotes outdegree 0
    while (m--) {
        int u, v; cin >> u >> v;
        edges[u] = v;
    }

    vector<int> level(n);
    int largest_scc = -1;
    int level_counter = 0;

    for (int u = 0; u < n; ++u) {
        int v = u, level_u = level_counter;

        // Traverse all unvisited nodes in subgraph
        while (v != -1 && !level[v]) {
            level[v] = level_counter++;
            v = edges[v];
        }

        if (v != -1 && level[v] >= level_u) {
            // Encountered a previously visited node in same subgraph
            largest_scc = max(largest_scc, level_counter - level[v]);
        }
    }

    cout << largest_scc << endl;

    return EXIT_SUCCESS;
}


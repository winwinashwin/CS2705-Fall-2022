/**
 * @file     A03_Q01_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char **argv) {
    /**
     * Logic: The idea is similar to a topological sort. We know that all nodes with out degree 0
     *        are secure. We push such nodes into a queue and process the queue. Every node in queue
     *        is marked secure and the out degree of all parent nodes of the current node is decremented
     *        by 1. Following the update all parents of current node with the updated out degree as
     *        0 is pushed to the queue.
     *
     */
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);  // Graph as adjacency list
    vector<int> out_degree(n);   // Outdegree of all nodes
    vector<bool> is_secure(n);

    while (m--) {
        int u, v;
        cin >> u >> v;
        out_degree[u]++;
        adj[v].push_back(u);  // We read transpose graph to extract parents easily
    }

    // Only nodes with outdegree 0, i.e secure nodes are pushed to the queue.
    queue<int> q;
    for (int u = 0; u < n; ++u)
        if (!out_degree[u]) 
            q.push(u);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        is_secure[u] = 1;  // Mark node as secure
        for (auto v : adj[u]) out_degree[v]--;  // Update outdegree of parents

        // Check parents that are secure
        for (auto v : adj[u])
            if (!out_degree[v])
                q.push(v);
    }

    // Print secure rooms in ascending order
    for (int u = 0; u < n; ++u) {
        if (is_secure[u]) cout << u << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}

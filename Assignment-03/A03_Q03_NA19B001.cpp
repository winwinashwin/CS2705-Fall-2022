/**
 * @file     A03_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Logic: A and B are k-strangers if length of shortest path between A and B is greater than k. 
 *        We do a BFS starting at each node maintaining path length during traversal. Answer is 
 *        updated when nodes with path length > k are encountered. If (u,v) are k-strangers counter
 *        is updated during BFS starting at u as well v which leads to double counting. Hence final
 *        result is halved.
 */

// BFS starting at u
int bfs(const vector<vector<int>>& adj, const int k, int u) {
    int n_pairs = 0, level = 0, n = adj.size();

    vector<bool> visited(n, false);

    queue<int> q;
    visited[u] = true;
    q.push(u);
    while (!q.empty()) {
        int s = q.size();
        level++;
        while (s--) {
            int v = q.front(); q.pop();

            for(int w : adj[v]) {
                if (visited[w]) continue;
                visited[w] = true;
                if (level > k) n_pairs++;
                q.push(w);
            }
        }
    }

    // All pairs (u,v) such that v in unreachable from u are also k-strangers
    for (int v = 0; v < n; ++v) if (!visited[v]) n_pairs++;

    return n_pairs;
}

int main(int argc, char **argv) {
    int n, k, p; cin >> n >> k >> p;
    vector<vector<int>> adj(n);

    while (p--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int n_pairs = 0;
    for (int u = 0; u < n; ++u)
        n_pairs += bfs(adj, k, u);

    cout << n_pairs/2 << endl;
    return EXIT_SUCCESS;
}

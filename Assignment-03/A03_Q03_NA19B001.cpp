/**
 * @file     A03_Q03_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Logic: A and B are k-strangers if length of shortest path between A and B is > k. We do a BFS
 *        starting at each node maintaining path length during traversal. Answer is updated when
 *        nodes with path length > k are encountered. If (u,v) are k-strangers counter is updated
 *        during BFS starting at u as well v which leads to double counting which is taken care of
 *        by halving the final result
 */

vector<vector<int>> adj;  // Graph as adjacency list
int n, k, n_pairs;

// BFS starting at u
void bfs(int u) {
    vector<bool> visited(n, false);

    int level = 0;
    queue<int> q;
    visited[u] = true;
    q.push(u);
    while (!q.empty()) {
        int s = q.size();
        level++;
        while (s--) {
            int v = q.front();
            q.pop();

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
}

int main(int argc, char **argv) {
    cin >> n >> k;
    adj.resize(n);
    int p; cin >> p;
    while (p--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    n_pairs = 0;
    for (int u = 0; u < n; ++u)
        bfs(u);

    cout << n_pairs/2 << endl;
    return EXIT_SUCCESS;
}

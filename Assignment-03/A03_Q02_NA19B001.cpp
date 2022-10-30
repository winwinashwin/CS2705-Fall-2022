/**
 * @file     A03_Q02_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char **argv) {
    /**
     * Logic: Since each city has at most one path going to another city that connects it to the
     *        other city, strongly connected components if present will be cycles in the graph.
     *        We do a simple DFS to detect cycles maintaing the levels of nodes during traversal.
     *        Once a cycle is detected, we can compute the SCC size using the level info of nodes.
     */

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);  // Graph as adjacency list
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<bool> visited(n,false);
    vector<int> level(n);

    int largest_scc = 0;
    for (int u = 0; u < n; ++u) {
        if (visited[u]) continue;

        // Depth First Search on graph starting at `u`
        fill(level.begin(), level.end(), 0);
        stack<int> st;
        st.push(u);
        while (!st.empty()) {
            int v = st.top(); st.pop();
            visited[v] = true;

            for (auto& w : adj[v]) {
                if (visited[w]) {
                    // Cycle found, compute size and update answer
                    largest_scc = max(largest_scc, level[v]-level[w]+1);
                    continue;
                }

                // update level
                level[w] = level[v] + 1;
                st.push(w);
            }
        }
    }

    cout << largest_scc << endl;
    return EXIT_SUCCESS;
}


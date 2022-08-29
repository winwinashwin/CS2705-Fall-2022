/**
 * @file     A01_Q01_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>

using namespace std;

struct Position {
    int i, j;
};

struct Query {
    Position top_left, bot_right;
};

// O(mnw) time, O(1) space
vector<int>
find_unoccupied_cp_v1(int m, int n, 
                      const vector<Position> &students, 
                      const vector<Query> &queries) {

    // Occupancy matrix
    vector<vector<int>> mat(m, vector<int>(n, 0));
    for (auto &st : students) mat[st.i][st.j] = 1;

    vector<int> result;
    result.reserve(queries.size());

    for (auto &q : queries) {
        int ans = 0;

        int di = q.bot_right.i - q.top_left.i;
        int dj = q.bot_right.j - q.top_left.j;

        for (int i = 0; i <= di; ++i) {
            for (int j = 0; j <= dj; ++j) {
                if (!mat[q.top_left.i + i][q.top_left.j + j]) ans++;
            }
        }

        result.push_back(ans);
    }
    return result;
}

// O(mn + w) time, O(mn) space
vector<int>
find_unoccupied_cp_v2(int m, int n, 
                      const vector<Position> &students, 
                      const vector<Query> &queries) {

    // Occupancy matrix
    // 1 denotes unoccupied, 0 denotes occupied
    vector<vector<int>> mat(m, vector<int>(n, 1));
    for (auto &st : students) mat[st.i][st.j] = 0;

    // 2D prefix sum
    vector<vector<int>> cnt(m, vector<int>(n, 0));
    cnt[0][0] = mat[0][0];
    for (int i = 1; i < n; ++i) cnt[0][i] = cnt[0][i-1] + mat[0][i];
    for (int i = 1; i < m; ++i) cnt[i][0] = cnt[i-1][0] + mat[i][0];
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            cnt[i][j] = cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1] + mat[i][j];
        }
    }

    vector<int> result;
    result.reserve(queries.size());

    for (auto &q : queries) {
        int ans = cnt[q.bot_right.i][q.bot_right.j];
        if (q.top_left.i > 0) ans -= cnt[q.top_left.i-1][q.bot_right.j];
        if (q.top_left.j > 0) ans -= cnt[q.bot_right.i][q.top_left.j-1];
        if (q.top_left.i > 0 && q.top_left.j > 0) ans += cnt[q.top_left.i-1][q.top_left.j-1];

        result.push_back(ans);
    }
    return result;
}

int main(int argc, char **argv) {
    int m, n, s, w;
    cin >> m >> n >> s >> w;

    char sep;  // For separator ','

    vector<Position> students(s);
    for (auto &st : students) cin >> st.i >> sep >> st.j;

    vector<Query> queries(w);
    for (auto &q : queries) {
        cin >> q.top_left.i >> sep;
        cin >> q.top_left.j >> sep;
        cin >> q.bot_right.i >> sep;
        cin >> q.bot_right.j;
    }

    vector<int> result = find_unoccupied_cp_v2(m, n, students, queries);
    for (auto &r : result) cout << r << endl;

    return EXIT_SUCCESS;
}


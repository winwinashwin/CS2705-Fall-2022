/**
 * @file     A02_Q02_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char **argv) {

    // Read input
    int n; cin >> n;
    vector<int> scores(n);
    for (int& sc : scores) cin >> sc;

    // `ans[i]` will store the index of the next greatest element to the right of `scores[i]`
    vector<int> ans(n);

    stack<int> st;
    st.push(0);

    for (int i = 1; i < n; ++i) {
        if (st.empty()) {
            st.push(i);
            continue;
        }

        // Pair the current element to stack.top() as long as current element is greater than
        // stack.top()
        while (!st.empty() && scores[st.top()] < scores[i]) {
            ans[st.top()] = i;
            st.pop();
        }

        st.push(i);
    }

    while (!st.empty()) {
        ans[st.top()] = -1;
        st.pop();
    }

    // Format output
    for(int i = 0; i < n; ++i) {
        if (ans[i] < 0) {
            cout << "Inf" << " ";
        } else {
            cout << ans[i]-i << " ";
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}

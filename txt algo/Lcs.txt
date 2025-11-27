#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

/*
    LCS FUNCTION
    Takes two strings a and b
    Returns:
        1) length of LCS
        2) the actual LCS sequence as a string
*/
pair<int,string> LCS(const string &a, const string &b) {
    int n = a.size(), m = b.size();

    // dp[i][j] = LCS length between:
    // a[0..i-1] and b[0..j-1]
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    // ------------------------------
    // BUILDING THE DP TABLE
    // ------------------------------
    // If characters match → extend LCS
    // If not match → take max from top or left
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;     // match → diagonal + 1
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]); // choose best option
        }
    }

    // ------------------------------
    // RECONSTRUCTING THE LCS SEQUENCE
    // ------------------------------
    // Start from bottom-right and move backward
    string seq = "";
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            // Characters are part of LCS → add to sequence
            seq.push_back(a[i-1]);
            i--, j--;     // move diagonal
        }
        else {
            // Move in direction of larger DP value
            if (dp[i-1][j] > dp[i][j-1])
                i--;      // move up
            else
                j--;      // move left
        }
    }

    // sequence is built backwards → reverse it
    reverse(seq.begin(), seq.end());

    // Return both LCS length + actual sequence
    return {dp[n][m], seq};
}

// ---------------------------------------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        string a, b;
        cin >> a >> b;

        auto result = LCS(a, b);

        cout << result.first << "\n";     // LCS length
        cout << result.second << "\n";    // LCS sequence

        if (T) cout << "\n"; // blank line between tests
    }
}
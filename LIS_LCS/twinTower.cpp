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
pair<int,vector<int>> LCS(const vector<int> &a, const vector<int> &b) {
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
    vector<int> seq;
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

    int n, m;
    int p=0;
    while (cin >> n >> m) {
        if (n==0 && m==0) break;
        vector<int> a(n);
        vector<int> b(m);
        for (int i=0; i<n; i++) {
            cin>>a[i];
        }
        for (int i=0; i<m; i++) {
            cin>>b[i];
        }
        auto result = LCS(a, b);

        cout<< "Twin Towers #"<<p+1<< "\n";
        p++;
        cout<< "Number of Tiles : " << result.first << "\n";


    }
}
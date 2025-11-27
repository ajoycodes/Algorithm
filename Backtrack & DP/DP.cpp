#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
using namespace std;

//------------------------------------
// 1) CLASSIC 0/1 KNAPSACK
//------------------------------------
int knapsack(vector<int> &w, vector<int> &val, int W) {
    int n = w.size();
    vector<int> dp(W+1, 0);

    for (int i = 0; i < n; i++) {
        for (int cap = W; cap >= w[i]; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w[i]] + val[i]);
        }
    }
    return dp[W];
}

//------------------------------------
// 2) SUBSET SUM (boolean)
//------------------------------------
bool subsetSum(vector<int> &a, int target) {
    vector<bool> dp(target+1, false);
    dp[0] = true;

    for (int x : a) {
        for (int s = target; s >= x; s--) {
            dp[s] = dp[s] || dp[s-x];
        }
    }
    return dp[target];
}

//------------------------------------
// 3) LCS (DP table)
//------------------------------------
int LCS(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    return dp[n][m];
}

//------------------------------------
// 4) LIS (O(n^2) DP)
//------------------------------------
int LIS(vector<int> &a) {
    int n = a.size();
    vector<int> dp(n, 1);
    int best = 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1),
                best = max(best, dp[i]);

    return best;
}

int main() {
    vector<int> w = {3,4,5};
    vector<int> val = {30,40,50};
    int W = 6;

    cout << "Knapsack: " << knapsack(w, val, W) << "\n";

    return 0;
}
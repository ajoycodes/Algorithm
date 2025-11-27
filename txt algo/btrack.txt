#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
using namespace std;

vector<int> nums;      // input
vector<int> path;      // current selection
vector<bool> used;     // for permutations

//------------------------------------
// 1) GENERATE COMBINATIONS (choose r from n)
//------------------------------------
void combine(int idx, int taken, int r) {
    if (taken == r) {
        // print or store the combination
        for (int x : path) cout << x << " ";
        cout << "\n";
        return;
    }

    for (int i = idx; i < nums.size(); i++) {
        path.push_back(nums[i]);
        combine(i + 1, taken + 1, r);
        path.pop_back();
    }
}

//------------------------------------
// 2) GENERATE PERMUTATIONS
//------------------------------------
void permute() {
    if (path.size() == nums.size()) {
        for (int x : path) cout << x << " ";
        cout << "\n";
        return;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        permute();
        path.pop_back();
        used[i] = false;
    }
}

//------------------------------------
// 3) N-QUEENS / CONSTRAINT TEMPLATE
//------------------------------------
int n;
vector<int> colUsed, diag1, diag2;  // constraints: col, diag, anti diag

void nqueen_dfs(int row) {
    if (row == n) {
        // valid solution
        return;
    }

    for (int col = 0; col < n; col++) {
        if (colUsed[col] || diag1[row+col] || diag2[row-col+n]) continue;

        colUsed[col] = diag1[row+col] = diag2[row-col+n] = 1;

        nqueen_dfs(row+1);

        colUsed[col] = diag1[row+col] = diag2[row-col+n] = 0;
    }
}


int main() {
    nums = {1,2,3,4};
    used.assign(nums.size(), false);

    // Example: generate all 2-combinations
    combine(0, 0, 2);

    // Example: generate permutations
    permute();

    // Example: N-Queens (n=8)
    n = 8;
    colUsed.assign(n, 0);
    diag1.assign(2*n, 0);
    diag2.assign(2*n, 0);
    nqueen_dfs(0);

    return 0;
}
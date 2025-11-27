#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

int LIS(vector<int> &a) {
    vector<int> temp;
    for (int x : a) {
        //Non-decreasing hole "upper_bound" use kora lagbe!
        auto it = lower_bound(temp.begin(), temp.end(), x);
        if (it == temp.end()) temp.push_back(x);
        else *it = x;
    }
    return temp.size();
}

//Minimum deletion to make array sorted = n - LIS(a)
//LIS on decreasing sequence -> multiply all in array by -1.

//For 2d
/*
int solve_pairs(vector<pair<int,int>>& v){
    sort(v.begin(), v.end(), [&](auto &a, auto &b){
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });

    vector<int> seq;
    for(auto &p : v) seq.push_back(p.second);

    return LIS(seq);
}
*/


/*
 *
 *
 *
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        cout << LIS(a) << "\n";
        if (T) cout << "\n";
    }
}

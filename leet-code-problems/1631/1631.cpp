// #pragma GCC target("popcnt")  // if solution involves bitset
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#ifdef croquete  // BEGIN TEMPLATE ----------------------|
#include "dbg.h"
#define fio freopen("in.txt", "r", stdin)
#else
#define dbg(...)
#define fio cin.tie(0)->sync_with_stdio(0)
#endif
#define ll           long long
#define vll          vector<ll>
#define vvll         vector<vll>
#define pll          pair<ll, ll>
#define vpll         vector<pll>
#define all(xs)      xs.begin(), xs.end()
#define rep(i, a, b) for (ll i = (a); i  < (ll)(b); ++i)
#define per(i, a, b) for (ll i = (a); i >= (ll)(b); --i)
#define eb           emplace_back
#define cinj         cin.iword(0)  = 1, cin
#define coutj        cout.iword(0) = 1, cout
template <typename T>  // read vector
istream& operator>>(istream& is, vector<T>& xs) {
    assert(!xs.empty());
    rep(i, is.iword(0), xs.size()) is >> xs[i];
    return is.iword(0) = 0, is;
} template <typename T>  // print vector
ostream& operator<<(ostream& os, vector<T>& xs) {
    rep(i, os.iword(0), xs.size()) os << xs[i] << ' ';
    return os.iword(0) = 0, os;
} void solve();
signed main() {
    fio;
    ll t = 1;
    cin >> t;
    while (t--) solve();
}  // END TEMPLATE --------------------------------------|

vector<pair<int, int>> ds = { {0,1}, {1,0}, {0,-1}, {-1,0} };


class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        pair<int, int> destination = {(int)heights.size()-1, (int)heights[0].size()-1};
        priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
        pq.push({0,0,0});
        vector<vector<int>> efforts(heights.size(), vector<int>(heights[0].size(), INT_MAX));
        efforts[0][0] = 0;

        while (!pq.empty()) {
            auto [effort, x, y] = pq.top(); pq.pop();
            if (x == destination.first && y == destination.second) return effort;

            for (auto& d : ds) {
                int nx = x + d.first;
                int ny = y + d.second;

                if (nx < 0 || nx >= heights.size() || ny < 0 || ny >= heights[0].size()) continue;

                int newEffort = max(effort, abs(heights[nx][ny] - heights[x][y]));
                if (newEffort < efforts[nx][ny]) {
                    efforts[nx][ny] = newEffort;
                    pq.push({newEffort, nx, ny});
                }
            }
        }

        return efforts[destination.first][destination.second];
    }
};

void solve() {
    Solution sol;
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};

    double result = sol.minimumEffortPath(heights);

    cout << result << "\n";
}

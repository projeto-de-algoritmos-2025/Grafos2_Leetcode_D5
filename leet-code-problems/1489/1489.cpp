// #pragma GCC target("popcnt")  // if solution involves bitset
#include <bits/stdc++.h>
#include <queue>
#include <vector>
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
#define vi           vector<int>
#define vvi          vector<vi>
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

#define u(a) a[0]
#define v(a) a[1]
#define w(a) a[2]

/**
 *
 * Disjoint Set Union (Union-Find) data structure. from euyogi competitive programming notebook
 * @reference{https://github.com/euyogi/Notebook-CompetitiveProgramming}
 *
 */
struct DSU {
    vll parent, size;

    /**
     *  @param  sz  Size.
    */
    DSU(ll sz) : parent(sz), size(sz, 1) { iota(all(parent), 0); }

    /**
     *  @param  x  Element.
     *  Time complexity: ~O(1)
    */
    ll find(ll x) {
        assert(0 <= x && x < parent.size());
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    /**
     *  @param  x, y  Elements.
     *  Time complexity: ~O(1)
    */
    void merge(ll x, ll y) {
        ll a = find(x), b = find(y);
        if (size[a] > size[b]) swap(a, b);
        parent[a] = b;
        if (a != b) size[b] += size[a], size[a] = 0;
    }

    /**
     *  @param  x, y  Elements.
     *  Time complexity: ~O(1)
    */
    bool same(ll x, ll y) { return find(x) == find(y); }
};


class Solution {
public:
    vvi findCriticalAndPseudoCriticalEdges(int n, vvi& edges) {
        int m = (int)edges.size();
        vvi newEdges;

        rep(i, 0, m) {
            newEdges.push_back({u(edges[i]), v(edges[i]), w(edges[i]), (int)i});
        }

        sort(all(newEdges), [](const vi& a, const vi& b) {
            return w(a) < w(b);
        });

        int originalWeight = kruskal(n, newEdges);

        dbg(originalWeight);

        vvi critical, pseudoCritical;

        rep(i, 0, m) {
            vvi edgesWithoutI;

            rep(j, 0, m) {
                if (j != i) edgesWithoutI.push_back(newEdges[j]);
            }

            int weightWithoutI = kruskal(n, edgesWithoutI);
            dbg(weightWithoutI);

            if (weightWithoutI > originalWeight) {
                dbg("critical detected", newEdges[i]);
                critical.push_back(newEdges[i]);
            } else {
                vvi edgesWithI = {newEdges[i]};

                rep(j, 0, m) {
                    if (j != i) edgesWithI.push_back(newEdges[j]);
                }

                int weightWithI = kruskal(n, edgesWithI);

                if (weightWithI == originalWeight) {
                    pseudoCritical.push_back(newEdges[i]);
                }
            }
        }

        vvi result = {vi(), vi()};

        for (auto& a : critical) result[0].push_back(a[3]);
        for (auto& a : pseudoCritical) result[1].push_back(a[3]);

        return result;
    }
private:
    int kruskal(int n, vvi& edges) {
        DSU dsu(n);
        int total = 0;

        for (auto& a : edges) {

            if (!dsu.same(u(a), v(a))) {
                dsu.merge(u(a), v(a));
                total += w(a);
            }
        }


        if (dsu.size[dsu.find(0)] != n) return INT_MAX;

        return total;
    }
};

void solve() {
    Solution sol;

    vvi edges = {{0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,4,3},{3,4,3},{1,4,6}};
    vvi result = sol.findCriticalAndPseudoCriticalEdges(5, edges); // expected: [[0,1],[2,3,4,5]]


    dbg(result);
    cout << result << '\n';
}

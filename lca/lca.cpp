#include <bits/stdc++.h>
#define ull unsigned long long
#define FILES                      \
    freopen("lca.in", "r", stdin); \
    freopen("lca.out", "w", stdout);
#define CMAX 15485863
#define fastio std::ios_base::sync_with_stdio(NULL), cin.tie(NULL), cout.tie(NULL);
#define mp make_pair
#define INF 1e18
#define mod 666013
#define ll long long
#define SMAX 300
#define MAX 100000
#define pb push_back
#define add emplace_back
#define void inline void
#define int ll
using namespace std;
bool check[MAX + 5];
int n, m, f[MAX + 5], cost[MAX + 5], a, b, best = -1;
pair<int, int> ans;
vector<int> v[MAX + 5];
vector<pair<int, int>> rmq[MAX + 5];
vector<pair<int, int>> euler;
void dfs(int x, int h)
{
    check[x] = 1;
    euler.add(mp(x, h));
    f[x] = euler.size();
    for (auto i : v[x])
    {
        if (!check[i])
        {
            dfs(i, h + 1);
            euler.add(mp(x, h));
        }
    }
}
pair<int, int> Min(pair<int, int> a, pair<int, int> b)
{
    return (a.second > b.second ? b : a);
}
pair<int, int> Lca(int a, int b)
{
    int d = max(f[a], f[b]) - min(f[a], f[b]) + 1, p = 1, e = 0;
    while (p <= d)
        p *= 2, e++;
    p >>= 1, e--;
    return Min(rmq[e][min(f[a], f[b]) - 1], rmq[e][max(f[a], f[b]) - p]);
}
signed main()
{
    fastio
            FILES
                cin >>
        n >> m;
    for (int i = 1; i < n; ++i)
    {
        cin >> a;
        v[i + 1].add(a), v[a].add(i + 1);
    }
    dfs(1, 1);
    for (int i = 0; i < euler.size(); ++i)
        rmq[0].add(euler[i]);
    int cnt = euler.size(), tot = euler.size();
    for (int i = 1; i <= log2(cnt); ++i)
    {
        tot -= (1 << (i - 1));
        for (int j = 1; j <= tot; ++j)
            rmq[i].add(Min(rmq[i - 1][j - 1], rmq[i - 1][j + (1 << (i - 1)) - 1]));
    }
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        cin >> a >> b;
        pair<int, int> lca = Lca(a, b);
        cout << lca.first << '\n';
    }
}

#include <bits/stdc++.h>
#define ull unsigned long long
#define FILES                         \
    freopen("xormax.in", "r", stdin); \
    freopen("xormax.out", "w", stdout);
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
using namespace std;
int n, tnodes, v[MAX + 5], start, stop, s;
struct Trie
{
    int fr[21] = {0};
    bool isEnd;
};
Trie tr[MAX * 4 + 5];
void add(int x, int j)
{
    int node = 0;
    for (int i = 20; i >= 0; --i)
    {
        int b = (1LL << i);

        if (x & b)
        {
            if (tr[node].fr[i])
                node = tr[node].fr[i];
            else
            {
                tnodes++;
                tr[node].fr[i] = tnodes;
                node = tnodes;
            }
        }
    }
    tr[node].isEnd = 1;
}
void read(int &a)
{
    a = 0;
    char c;
    while (1)
    {
        c = getchar();
        if (c < '0' || c > '9')
            break;
        a = a * 10 + c - '0';
    }
}
int main()
{
    fastio
        FILES
            read(n);
    int xm = 0, best = -1;
    for (int i = 1; i <= n; ++i)
    {
        read(v[i]);
        xm ^= v[i];
        int node = 0, newxor = xm;
        for (int j = 20; j >= 0; --j)
        {
            int b = (1LL << j);
            if ((xm & b) == 0)
            {
                if (tr[node].fr[j])
                {
                    node = tr[node].fr[j];
                    newxor ^= (1LL << j);
                }
            }
        }
        while (1)
        {
            if (tr[node].isEnd)
                break;
            bool ok = 0;
            for (int j = 0; j <= 20; ++j)
            {
                if (tr[node].fr[j])
                {
                    ok = 1;
                    newxor ^= (1 << j);
                    node = tr[node].fr[j];
                    break;
                }
            }
            if (!ok)
                break;
        }
        if (newxor > best)
            best = newxor, stop = i;
        add(xm, i);
    }
    xm = 0;
    for (int i = stop; i >= 1; --i)
    {
        xm ^= v[i];
        if (xm == best)
        {
            cout << best << ' ' << i << ' ' << stop;
            exit(0);
        }
    }
}
#include <bits/stdc++.h>
#define foru(i, a, b) for(int i = int(a); i <= int(b); i++)
#define ng(x) (x <= n ? x + n : x - n)
#define pb push_back
#define sz(a) (int)a.size()
using namespace std;

const int N = 100005;

int n, m, num[N], low[N], dd[N], t_time, color[N];
vector< int > adj[N];
stack< int > stk;
bool ok = true;

void colored(int u, int x) {
    if (color[u] == 3-x) ok = false; else color[u] = x;
    if (color[ng(u)] == x) ok = false; else color[ng(u)] = 3-x;
}

void dfs(int u) {
    num[u] = low[u] = ++t_time;
    stk.push(u);
    foru(i, 0, sz(adj[u])-1) {
        int v = adj[u][i];
        if (color[v] == 2) colored(u, 2);
        if (num[v] == -1) continue;
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            dfs(v);  low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == num[u]) {
        if (!color[u]) colored(u, 1);
        int v;
        do {
            v = stk.top();  stk.pop();
            colored(v, color[u]);
            num[v] = -1;
        } while (v != u);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    //freopen("a.txt", "r", stdin);
    //freopen("b.txt", "w", stdout);

    cin >> m >> n;
    foru(i, 1, m) {
        int u, v;  cin >> u >> v;
        if (u < 0) u = abs(u) + n;
        if (v < 0) v = abs(v) + n;
        adj[ng(u)].pb(v);
        adj[ng(v)].pb(u);
    }
    foru(u, 1, 2*n) if (!num[u]) dfs(u);
    ///answer
    if (ok) {
        cout << "YES\n";
        int cities = 0;
        foru(u, 1, n) if (color[u] == 1) cities++;
        cout << cities << '\n';
        foru(u, 1, n) if (color[u] == 1) cout << u << ' ' ;
    } else cout << "NO\n";

    return 0;
}

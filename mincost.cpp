#include <bits/stdc++.h>

using namespace std;

#define REPN(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a, _b = b; i <= _b; ++i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(a) (int)a.size()

typedef pair<int, int> pii;
typedef vector<int> vi;
struct edge { int vertex, f, capacity, cost; };

const int maxN = 105;
const int inf  = 2147483647;

int n, m, k, sta, fin, maxFlow, minCost;
vi adj[maxN];
vector<edge> e;
edge a[maxN][maxN];

int dist[maxN];
pii trace[maxN];

int foundSPA()
{
    priority_queue<pii, vector<pii>, greater<pii>> heap;
    FOR(i, 1, n + 1) dist[i] = inf;
    heap.push({0, 0});
    while (!heap.empty())
    {
        int u = heap.top().se, d = heap.top().fi;
        heap.pop();
        if (d != dist[u]) continue;
        for (int i : adj[u])
        {
            if (e[i].f < e[i].capacity && dist[e[i].vertex] > d + e[i].cost)
            {
                dist[e[i].vertex] = d + e[i].cost;
                heap.push({dist[e[i].vertex], e[i].vertex});
                trace[e[i].vertex] = {u, i};
            }
        }
    }

    return dist[n + 1] < inf;
}

void augment()
{
    int delta = inf;
    for (int v = n + 1; v; v = trace[v].fi)
        delta = min(delta, e[trace[v].se].capacity - e[trace[v].se].f);
    maxFlow += delta;
    minCost += delta * dist[n + 1];
    for (int v = n + 1; v; v = trace[v].fi)
    {
        int i = trace[v].se, rev = i + 1 - 2 * (i%2);
        e[i].f += delta;
        e[rev].f -= delta;
    }
}

void addEdge(int u, int v, int capacity, int cost)
{
    e.pb({v, 0, capacity, cost});   adj[u].pb(sz(e) - 1);
    e.pb({u, 0,       0, -cost});   adj[v].pb(sz(e) - 1);
}

void read()
{
    cin >> n >> m >> k >> sta >> fin;
    int ui, vi, ci, di;
    REPN(i, m)
    {
        cin >> ui >> vi >> ci >> di;
        a[ui][vi] = a[vi][ui] = {0, 0, di, ci};
    }
    FOR(ui, 1, n) FOR(vi, 1, n) if (a[ui][vi].cost + a[ui][vi].capacity)
        addEdge(ui, vi, a[ui][vi].capacity, a[ui][vi].cost);

    addEdge(0, sta, k, 0);
    addEdge(fin, n + 1, k, 0);
}

void answer()
{
    if (maxFlow != k)
    {
        cout << -1 << endl;
        return;
    }
    cout << minCost << endl;
    FOR(u, 1, n) for (int i : adj[u])
        if (e[i].vertex != n + 1 && e[i].f > 0)
            cout << u << ' ' << e[i].vertex << ' ' << e[i].f << endl;
    cout << "0 0 0\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    freopen("MINCOST.inp", "r", stdin);

    read();
    while (foundSPA()) augment();
    answer();
}


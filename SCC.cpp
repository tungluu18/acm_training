#include <bits/stdc++.h>

using namespace std;

typedef vector <int> vi;

const int maxN = 100005;

int n, m, visited[maxN];
vi adj[maxN], adjT[maxN], visStack;

void read() {
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }
}

void dfs(int u) {
    visited[u] = 1;
    for (int v : adj[u]) {
        if (visited[v]) continue;
        dfs(v);
    }
    visStack.push_back(u);
}

void scc(int u) {
    visited[u] = 1;
    for (int v : adjT[u]) {
        if (visited[v]) continue;
        scc(v);
    }
}

int numberSCC = 0;
void kosaraju() {
    for (int u = 1; u <= n; ++u)
        if (!visited[u]) dfs(u);

    for (int u = 1; u <= n; ++u) visited[u] = 0;
    while (!visStack.empty()) {
        int u = visStack.back();
        visStack.pop_back();
        if (visited[u]) continue;
        numberSCC++;
        scc(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("a.txt", "r", stdin);
    read();
    kosaraju();
    cout << numberSCC << endl;
}

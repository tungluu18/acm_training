#include <bits/stdc++.h>

using namespace std;

const int maxN = 111;
const int oo = 1e7+111;

int  c[maxN][maxN], n,
     matchX[maxN], matchY[maxN], source[maxN], d[maxN],
     trace[maxN], fx[maxN], fy[maxN];
queue<int> Q;

void read() {
     cin >> n;
     for (int i = 1; i <= n; ++i) {
          for (int j = 1; j <= n; ++j) {
               c[i][j] = oo;
          }
     }
     for (int u, v, w; (cin >> u >> v >> w); ) {
          c[u][v] = w;
     }
}

void init() {
     memset(matchX, 0, sizeof(matchX));
     memset(matchY, 0, sizeof(matchY));
     memset(fx,     0, sizeof(fx));
     memset(fy,     0, sizeof(fy));
}

inline int getC(int i, int j) {
     return c[i][j] - fx[i] - fy[j];
}

void initBFS(int start) {
     while (!Q.empty()) Q.pop();
     for (int i = 1; i <= n; ++i) {
          trace[i] = 0;
          d[i] = getC(start, i);
          source[i] = start;
     }
     Q.push(start);
}

int findAugmentPath(int start) {
     while (!Q.empty()) {
          int u = Q.front();  Q.pop();
          for (int v = 1; v <= n; ++v) if (!trace[v]) {
               if (d[v] > getC(u, v)) {
                    d[v] = getC(u, v);
                    source[v] = u;
               }
               if (!getC(u, v)) {
                    trace[v] = u;
                    if (!matchY[v]) return v;
                    Q.push(matchY[v]);
               }
          }
     }
     return 0;
}

int subX_addY(int start) {
     int delta = oo;
     for (int v = 1; v <= n; ++v) if (!trace[v]) {
          delta = min(delta, d[v]);
     }
     fx[start] += delta;
     for (int v = 1; v <= n; ++v) {
          if (trace[v]) {
               fx[matchY[v]] += delta;
               fy[v] -= delta;
          } else {
               d[v] -= delta;
          }
     }
     for (int v = 1; v <= n; ++v) if (!trace[v] && !d[v]) {
          trace[v] = source[v];
          if (!matchY[v]) return v;
          Q.push(matchY[v]);
     }
     return 0;
}

void enlarge(int finish) {
     for (int v = finish, u, next; v; v = next) {
          u = trace[v];
          next = matchX[u];
          matchX[u] = v, matchY[v] = u;
     }
}

void Hungarian() {
     init();
     for (int start = 1, finish; start <= n; ++start) {
          initBFS(start);
          while ((finish = findAugmentPath(start)) == 0) {
               if ((finish = subX_addY(start)) > 0) break;
          }
          enlarge(finish);
     }
}

void answer() {
     int minCost = 0;
     for (int u = 1, v; u <= n; ++u) {
          v = matchX[u];
          if (!v || c[u][v] == oo) continue;
          minCost += c[u][v];
     }
     cout << minCost << "\n";
     for (int u = 1, v; u <= n; ++u) {
          v = matchX[u];
          if (!v || c[u][v] == oo) continue;
          cout << u << " " << v << "\n";
     }
}

main() {
     if (fopen("a.txt", "r")) {
          freopen("a.txt", "r", stdin);
     }
     ios_base::sync_with_stdio(false);
     read();
     Hungarian();
     answer();
}

//QTREE3 SPOJ
#include <bits/stdc++.h>
#define fu(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define N 100005

using namespace std;
typedef pair<int,int> pii;
typedef set<pii> setp;

int n,q,par[N],l[N],Ind[N],Head[N],color[N],nCh;
vector<int> a[N];
setp ss[N];

void direct(int u) {
    int i,v;
    for(i = 0; v = a[u][i]; i++)
        if (v != par[u]) {
            par[v] = u; l[v] = l[u] + 1;
            direct(v);
        }
}

void hld(int u) {
    if (Head[nCh] == 0) Head[nCh] = u;
    Ind[u] = nCh;
    int mm = -1;
    int i,v;
    for(i = 0; v = a[u][i]; i++)
        if (v != par[u])
        if (mm == -1 || (int)a[v].size() > (int)a[mm].size()) mm = v;
    if (mm > -1) hld(mm);
    for(i = 0; v = a[u][i]; i++)
        if (v != par[u] && v != mm) {
            nCh++;
            hld(v);
        }
}

void solve1(int u) {
    color[u] = 1 - color[u];
    if (color[u]) {
        ss[Ind[u]].insert(mp(l[u],u));
    } else {
        set<pii>::iterator it;
        it = ss[Ind[u]].lower_bound(mp(l[u],u));
        ss[Ind[u]].erase(it);
    }
}

void solve2(int u) {
    int mm = -1;
    set<pii>::iterator it;

    pii p; p=mp(0,0);
    while (1) {
        it=ss[Ind[u]].upper_bound(mp(0,0));
        if (it != ss[Ind[u]].end())
        if ((it->first) <= l[u]) mm = it->second;
        if (Ind[u] == 0) break; else u = par[Head[Ind[u]]];
    }
    cout << mm << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //freopen("a.txt","r",stdin);
    cin >> n >> q;
    int u, v, k;
    fu(i, 1, n-1) {
        cin >> u >> v;
        a[u].pb(v); a[v].pb(u);
    }
    fu(i, 1, n) a[i].pb(0);
    l[1] = 1; par[1] = 1;
    direct(1);
    hld(1);
    nCh--;
    fu(i, 0, nCh) ss[i].insert(mp(0,0));

    fu(i, 1, q) {
        cin >> k >> u;
        if (k == 0) solve1(u); else solve2(u);
    }
}

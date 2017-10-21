#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

string S;
int n, sa[N], key[N], tmp[N], lcp[N], k;

bool cmpSuf(int i, int j) {
    if (key[i] != key[j]) return key[i] < key[j];
    i += k, j += k;
    return (i < n && j < n) ? key[i] < key[j] : i > j;
}

void suffixArray(string S) {
    n = S.length();
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        key[i] = S[i];
    }
    for (k = 1; ; k *= 2) {
        sort(sa, sa + n, cmpSuf);
        for (int i = 1; i < n; ++i)
            tmp[i] = tmp[i - 1] + cmpSuf(sa[i - 1], sa[i]);
        for (int i = 0; i < n; ++i)
            key[sa[i]] = tmp[i];
        if (tmp[n - 1] == n - 1) break;
    }
}

void longComPre() {
    lcp[0] = 0;
    int q = 0;
    for (int i = 0; i < n; ++i) if (key[i]) {
        int j = sa[key[i] - 1];
        while (S[i + q] == S[j + q]) ++q;
        lcp[key[i]] = q;
        if (q) q--;
    }
}

int main() {
    freopen("A.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> S;
    suffixArray(S);
    longComPre();
    for (int i = 0; i < n; ++i)
        cout << lcp[i] << ' ' << S.substr(sa[i], n - sa[i]) << '\n';
}

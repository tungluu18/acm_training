//PALINX SPOJ
#include <bits/stdc++.h>
#define foru(i,a,b) for(int i = (a); i <= (b); i++)
#define ford(i,a,b) for(int i = (a); i >= (b); i--)
#define pb push_back
#define N 2000005
using namespace std;
struct node
{
    int cnt, s_end;
    node *a[26];
};
typedef vector<int> vec;
typedef long long llong;
node *root;
int n, m[N], f[N], dd[N];
vec st[N];
/*=============================================================================================*/
void read()
{
    scanf("%d",&n);
    int len;
    char ss[N];
    foru(i,1,n)
    {
        scanf("%d%s", &len, &ss);
        foru(j,0,len-1) st[i].push_back(int(ss[j])-97);
    }
}
/*=============================================================================================*/
node *neww()
{
    node *p;
    p = new(node);
    p->cnt = p->s_end = 0;
    foru(i,0,25) p->a[i] = NULL;
    return p;
}
/*=============================================================================================*/
void add(vec &s)
{
    int len = s.size();
    node *p = root;
    foru(i,0,len-1)
    {
        if (p->a[s[i]] == NULL) p->a[s[i]] = neww();
        p = p->a[s[i]];
        p->cnt += dd[i];
    }
    p->s_end++;
}
/*=============================================================================================*/
void manacher(vec &s)
{
    int len = s.size(), k = 0;
    m[k] = -1;
    foru(i,0,len-1)
    {
        m[++k] = s[i];
        m[++k] = -1;
        dd[i] = 0;
    }
    ///Manacher
    f[0] = 0;
    int L = 0, R = 0;
    foru(i,1,k)
    {
        if (i <= R) f[i] = min(f[L+R-i],R-i);
        else f[i] = 0;
        while (i-f[i] > 0 && i+f[i] < k && m[i-f[i]-1] == m[i+f[i]+1]) f[i]++;
        if (R < i+f[i]) R = i+f[i], L = i-f[i];
    }
    foru(i,1,k)
    {
        L = i-f[i], R = i+f[i];
        if (L == R && m[i] == -1) continue;
        if (R == k && L > 0) dd[(L-1)/2] = 1;
    }
    dd[len-1] = 1;
    //foru(i,0,len-1) cout << dd[i];  cout << endl;
}
/*=============================================================================================*/
int query(vec &s)
{
    int len = s.size(), res = 0;
    node *p = root;
    bool ok = true;
    foru(i,0,len-1)
    {
        if (p->a[s[i]] == NULL)
        {
            ok = false;
            break;
        }
        p = p->a[s[i]];
        if (dd[i]) res += p->s_end;
    }
    if (ok) res = res+p->cnt-p->s_end;
    //cout << res << endl;
    return res;
}
/*=============================================================================================*/
void solve()
{
    llong ans = 0LL;
    foru(i,1,n)
    {
        manacher(st[i]);
        add(st[i]);
    }
    foru(i,1,n)
    {
        reverse(st[i].begin(),st[i].end());
        manacher(st[i]);
        ans += llong(query(st[i]));
    }
    cout << ans << endl;
}
/*=============================================================================================*/
int main(void)
{
    //freopen("a.txt", "r", stdin);
    root = neww();
    read();
    solve();
}
/*=============================================================================================*/


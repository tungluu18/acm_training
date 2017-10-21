#include <stdio.h>
#include <algorithm>
using namespace std;

#define long long long

typedef pair<long, long> ii;
typedef pair<long, ii> triple;
#define X first
#define Y second

ii extended_gcd(long a, long b){
    ii qr, st;
    if (b==0) return ii(1, 0);
    else {
        qr=ii(a/b, a%b);
        st=extended_gcd(b, qr.Y);
        return ii(st.Y, st.X-qr.X*st.Y);
    }
}

long gcd(long a, long b){
    if (a==0) return b;
    else return gcd(b%a, a);
}

int main(){
    long p, q;
    ii ww;

    for (;;){
        if (scanf("%lld%lld", &p, &q) < 0) return 0;
        ww = extended_gcd(p, q);
        printf("%lld %lld %lld\n", ww.X, ww.Y, gcd(p, q));
    }
}



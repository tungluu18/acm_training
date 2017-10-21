#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

class FenwickTree {
    private :
        int f[MAXN];
    public :
        void update(int x, int value) {
            for (; x < MAXN; x += (x & (-x))) {
                f[x] += value;
            }
        }
        int get(int x) {
            int result = 0;
            for (; x > 0; x -= (x & (-x))) {
                result += f[x];
            }
            return result;
        }
};


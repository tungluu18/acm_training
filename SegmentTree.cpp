#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
private :
    vector <int> T, lazy;
    int n;

    void passInfor(int node, int nodeL, int nodeR) {
        if (lazy[node] == -1) return;
        T[node] = lazy[node];
        if (nodeL == nodeR) return;
        lazy[2 * node] = lazy[2 * node + 1] = lazy[node];
        lazy[node] = -1;
    }

    void update(int node, int nodeL, int nodeR, int left, int right, int value) {
        passInfor(node, nodeL, nodeR);
        if (nodeR < left || nodeL > right) return;
        if (left <= nodeL && nodeR <= right) {
            lazy[node] = value;
            passInfor(node, nodeL, nodeR);
            return;
        }
        int nodeMid = (nodeL + nodeR) / 2;
        update(node * 2, nodeL, nodeMid, left, right, value);
        update(node * 2 + 1, nodeMid + 1, nodeR, left, right, value);
        T[node] = max(T[2 * node], T[2 * node + 1]);
    }

    int get(int node, int nodeL, int nodeR, int left, int right) {
        passInfor(node, nodeL, nodeR);
        if (nodeR < left || nodeL > right) return -1e9;
        if (left <= nodeL && nodeR <= right) {
            return T[node];
        }
        int nodeMid = (nodeL + nodeR) / 2;
        return max(get(2 * node, nodeL, nodeMid, left, right),
                   get(2 * node + 1, nodeMid + 1, nodeR, left, right));
    }

public :
    SegmentTree(int n) {
        this->n = n;
        T.resize(4 * n);
        lazy.resize(4 * n);
    }

    void update(int left, int right, int value) {
        update(1, 1, n, left, right, value);
    }

    int get(int left, int right) {
        return get(1, 1, n, left, right);
    }
};


int main() {
    SegmentTree IT(4);
    IT.update(2, 3, 4);
    IT.update(1, 2, 5);
    IT.update(3, 3, 10);
    cout << IT.get(2, 4);
}

void build(int node = 1, int left = 1, int right = n) {
    if (left == right) {
        tree[node] = {c[left], 0};
        return;
    }
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    tree[node] = {tree[node * 2].fi + tree[node * 2 + 1].fi, 0};
}

void lazy(int node, int ll, int rr) {
    if (tree[node].se & 1) {
        tree[node].fi = (rr - ll + 1) - tree[node].fi;  ///switch
    }
    if (ll < rr) {
        tree[node * 2].se += tree[node].se;
        tree[node * 2 + 1].se += tree[node].se;
    }
    tree[node].se = 0;
}

int get(int u, int v, int node = 1, int ll = 1, int rr = n) {
    lazy(node, ll, rr);

    if (u > rr || v < ll) return 0;
    if (u <= ll && rr <= v) return tree[node].fi;

    int mi = (ll + rr) / 2;
    return get(u, v, node * 2, ll, mi) + get(u, v, node * 2 + 1, mi + 1, rr);
}

void update(int u, int v, int node = 1, int ll = 1, int rr = n) {
    lazy(node, ll, rr);

    if (u > rr || v < ll) return;
    if (u <= ll && rr <= v) {
        tree[node].se = 1;
        lazy(node, ll, rr);
        return;
    }

    int mi = (ll + rr) / 2;
    update(u, v, node * 2, ll, mi);
    update(u, v, node * 2 + 1, mi + 1, rr);
    tree[node].fi = tree[node * 2].fi + tree[node * 2 + 1].fi;
}
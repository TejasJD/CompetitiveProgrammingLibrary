#include "bits/stdc++.h"
#define ll long long
using namespace std;

// Single Node of segment tree
struct Node {
    ll val;

    Node() {}
    Node(ll _val) {
        val = _val;
    }
};

// Segment Tree Class
class Segtree {
private:
    int size;
    vector<Node> seg;

    // build main function
    void build(vector<int> &a, int x, int l, int r) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, 2*x + 1, l, m);
        build(a, 2*x + 2, m + 1, r);
        seg[x] = merge(seg[2*x + 1], seg[2*x + 2]);
    }

    // set main function
    void set(int i, int v, int x, int l, int r) {
        if(l == r) {
            seg[x] = v;
            return;
        }
        int m = (l + r) / 2;
        if(i <= m) set(i, v, 2*x + 1, l, m);
        else set(i, v, 2*x + 2, m+1, r);
        seg[x] = merge(seg[2*x + 1], seg[2*x + 2]);
    }

    // query main function
    Node query(int gl, int gr, int x, int l, int r) {
        if(r < gl || l > gr) return Node(0ll);
        if(gl <= l && r <= gr) return seg[x];

        int m = (l + r) / 2;
        Node lc = query(gl, gr, 2*x + 1, l, m);
        Node rc = query(gl, gr, 2*x + 2, m+1, r);
        return merge(lc, rc);
    }

public:
    // default constructor
    Segtree() {}

    // initialize a segment tree for array of size n
    Segtree(int n) {
        size = n;
        seg.assign(4 * size, Node(0ll));
    }

    // merge two nodes of segment tree
    Node merge(Node a, Node b) {
        Node res;
        res.val = a.val + b.val;
        return res;
    }

    // build segment tree
    void build(vector<int> &a) {
        build(a, 0, 0, size - 1);
    }

    // set ith element of segment tree to v
    void set(int i, int v) {
        set(i, v, 0, 0, size - 1);
    }

    // query range [l, r]
    Node query(int l, int r) {
       return query(l, r, 0, 0, size - 1); 
    }

    // debug segment tree (function to print tree)
    void getSeg() {
        for(auto it : seg) cout << it.val << " ";
        cout << "\n";
    }
};
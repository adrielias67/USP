#include <bits/stdc++.h>
using namespace std;

struct Sum {
    int x;
    Sum(): x(0) {}
    Sum(int _x): x(_x) {}
    friend Sum operator+(Sum a, Sum b) {
        return Sum(a.x + b.x);
    }
};

struct Min {
    int x;
    Min(): x(numeric_limits<int>::max()) {}
    Min(int _x): x(_x) {}
    friend Min operator+(Min a, Min b) {
        return Min(min(a.x, b.x));
    }
};

struct Max {
    int x;
    Max(): x(numeric_limits<int>::min()) {}
    Max(int _x): x(_x) {}
    friend Max operator+(Max a, Max b) {
        return Max(max(a.x, b.x));
    }
};

// To customize
struct RandomStuff {
    int x, k, t;

    RandomStuff(): x(-1), k(-1), t(-1) {} // Remember to set neutral element
    RandomStuff(int _x): x(_x), k(x ^ 321), t(x ^ 123) {}
    friend RandomStuff operator+(RandomStuff a, RandomStuff b) {
        if(a.x == -1 && a.k == -1 && a.t == -1) return b; // Check neutral element
        if(b.x == -1 && b.k == -1 && b.t == -1) return a; // Check neutral element
        return RandomStuff(a.k + b.t);
    }
};

template<typename Info>
class SegmentTree {
private:
    int size;
    vector<Info> info;

    void build(int nd, int l, int r, vector<int> &a) {
        if(l == r) info[nd] = Info(a[l]);
        else {
            int m = (l + r) / 2, x = nd + 1, y = nd + 2*(m - l + 1);
            build(x, l, m, a);
            build(y, m+1, r, a);
            info[nd] = info[x] + info[y];
        }
    }

    Info query(int nd, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return Info();
        if(ql <= l && r <= qr) return info[nd];
        int m = (l + r) / 2, x = nd + 1, y = nd + 2*(m - l + 1);
        return query(x, l, m, ql, qr) + query(y, m+1, r, ql, qr);
    }

    void update(int nd, int l, int r, int qpos, int qval) {
        if(l == r) info[nd] = qval;
        else {
            int m = (l + r) / 2, x = nd + 1, y = nd + 2*(m - l + 1);
            if(qpos <= m) update(x, l, m, qpos, qval);
            else update(y, m+1, r, qpos, qval);
            info[nd] = info[x] + info[y];
        }
    }

public:
    SegmentTree(vector<int> &a): size(a.size()), info(2*size - 1) {
        build(0, 0, size-1, a);
    }

    Info query(int ql, int qr) { // O(log size)
        assert(0 <= ql && ql <= qr && qr < size);
        return query(0, 0, size - 1, ql, qr);
    }

    void update(int qpos, int qval) { // O(log size)
        assert(0 <= qpos && qpos < size);
        update(0, 0, size - 1, qpos, qval);
    }
};

template<typename Seg>
void test() {
    vector<int> a = {3, 5, 100, 1, 20};

    Seg seg(a);

    cout << seg.query(0, 4).x << ' ';
    for(int i=0; i<5; i++) seg.update(i, 10);
    cout << seg.query(0, 4).x << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    vector<int> a;
    int n, q;
    cin >> n >> q;

    pair<int,int> intervalo[n];
    for(int i=0; i<n; i++){
        cin >> intervalo[i].first >> intervalo[i].second;
    }




    test<SegmentTree<Sum>>();
    test<SegmentTree<Min>>();
    test<SegmentTree<Max>>();
    test<SegmentTree<RandomStuff>>();
}
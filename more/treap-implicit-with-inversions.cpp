#include <bits/stdc++.h>
#define INF (1<<30)
using namespace std;

// TREAP

int Random() { return rand() << 15 | rand(); }

typedef struct node {
    int prior, value, cnt, menor;
    bool inv;
    node *l, *r;
    node (int value): prior(Random()), value(value), cnt(1), l(NULL), r(NULL){};
} *pnode;

int sz(pnode t){
    return t? t->cnt : 0;
}

void inverter(pnode t){
    if (t && t->inv){
        t->inv = false;
        swap (t->l, t->r);
        if (t->l) t->l->inv ^= 1;
        if (t->r) t->r->inv ^= 1;
    }
}

void update(pnode t){
    if (t){
        t->cnt = sz(t->l) + sz(t->r) + 1;
        t->menor = min({t->value, t->l?t->l->menor:INF, t->r?t->r->menor:INF});
    }
}

void split (pnode t, pnode &l, pnode &r, int key, int add = 0){
    inverter(t);
    l = r = NULL;
    if (!t) return;
    int pos = add + sz(t->l);
    if (pos < key)
        split(t->r, t->r, r, key, pos + 1), l = t;
    else
        split(t->l, l, t->l, key, add), r = t;
    update(t);
}

void merge (pnode &t, pnode l, pnode r){
    inverter(l);
    inverter(r);
    if (!l || !r)
        t = l? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    update(t);
}

int getposmin (pnode t, int key, int add = 0){
    inverter(t);
    if (t->value == key) return add + sz(t->l);
    if (!t->l || !t->r){
        if (!t->l) return getposmin(t->r, key, add + 1);
        return getposmin(t->l, key, add);
    }
    if (t->l->menor < t->r->menor)
        return getposmin(t->l, key, add);
    return getposmin(t->r, key, add + 1 + sz(t->l));
}

int solve (pnode &t, int k){
    int p = getposmin(t, k);
    pnode l, r, m;
    split(t, l, r, p + 1);
    split(l, l, m, p);
    delete m;
    if (l)
        l->inv = 1, inverter(l);
    merge(t, l, r);
    return p + k + 1;
}

#define N 100001
pair<int,int> arr[N];

int main(){
    while (true){
        int n;
        scanf ("%d", &n);
        if (!n) return 0;
        vector <pair<int,int>> v;
        for (int i = 0; i < n; i++){
            int a;
            scanf ("%d", &a);
            arr[i] = {a, i};
            v.push_back({a, i});
        }
        sort (v.begin(), v.end());
        pnode treap = NULL;
        for (int i = 0; i < v.size(); i++){
            int pos = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
            merge(treap, treap, new node(pos));

        }
        for (int i = 0; i < n; i++)
            printf ("%d%c", solve(treap, i), i + 1 == n? '\n' : ' ');
    }
    return 0;
}


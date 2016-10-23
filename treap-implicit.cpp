#include <bits/stdc++.h>

using namespace std;

// TREAP

int Random() { return rand() << 15 | rand(); }

typedef struct node {
    int prior, value, cnt;
    node *l, *r;
    node (int value): prior(Random()), value(value), cnt(1), l(NULL), r(NULL){};
} *pnode;

int sz(pnode t){
    return t? t->cnt : 0;
}

void update(pnode t){
    if (t){
        t->cnt = sz(t->l) + sz(t->r) + 1;
    }
}

// 0-indexed - l = [0, key-1], r = [key, inf)
void split (pnode t, pnode &l, pnode &r, int key, int add = 0){
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
    if (!l || !r)
        t = l? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    update(t);
}



int main(){
    pnode t = NULL;
    return 0;
}

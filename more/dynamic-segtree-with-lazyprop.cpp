#include <bits/stdc++.h>

using namespace std;

struct node;
node *newNode();

// Tested with a range of [1..10^9] and 2*10^5 queries
// Lazy propagation that uses less nodes than the usual


struct node {

    int value;
    bool lazy;

    node *l, *r;

    // -- CHANGE NEUTRAL VALUE
    node() : value(0), l(NULL), r(NULL), lazy (false) {}

    void expand (int a, int b){
        if (!l) l = newNode();
        if (!r) r = newNode();
        if (lazy){
            lazy = false;
            l->doLazy((a+b)/2-a+1);             // -- CHANGE CHILD UPDATION
            r->doLazy((b-(a+b)/2));             // -- CHANGE CHILD UPDATION
        }
    }

    void doLazy(int value){
        lazy = true;
        this->value = value;
    }

    int query (int a, int b, int i, int j){
        if (i > b || j < a) return 0;           // -- CHANGE NEUTRAL VALUE
        if (a >= i && b <= j) return value;
        expand(a, b);
        return l->query(a, (a + b)/2, i, j) + r->query((a + b)/2 + 1, b, i, j);     // -- CHANGE MERGE
    }

    // VALUE?
    void update (int a, int b, int i, int j){
        if (a > j || b < i) return;
        if (a >= i && b <= j){
            doLazy(b - a + 1);                  // -- CHANGE THE VALUE TO BE ASSIGNED
        } else{
            expand(a, b);
            l->update(a, (a+b)/2, i, j);
            r->update((a + b)/2 + 1, b, i, j);
            value = l->value + r->value;
        }
    }
};


node *newNode() {
    static int bufSize = 1e7;
    static node buf[(int) 1e7];
    assert(bufSize);
    return &buf[--bufSize];
}


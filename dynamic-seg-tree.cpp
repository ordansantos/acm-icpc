
struct node {
    long long value;
    node (long long value) : value(value) {}
};
node nil (){ return node(0); }
node merge (node a, node b){
    return a.value > b.value? a : b;
}
const int low = 0, up = 1000000000; // range

struct tree;
tree *new_tree();
struct tree {
    node value;
    tree *l, *r;
    tree() : value(nil()), l(NULL), r(NULL) {}
    node query (int i, int j, int a = low, int b = up){
        if (i > b || j < a) return nil();
        if (a >= i && b <= j) return value;
        return merge (l? l->query(i, j, a, (a + b)/2) : nil(), r? r->query(i, j, (a + b)/2 + 1, b) : nil());
    }
    void update (int i, node new_value, int a = low, int b = up){
        if (i > b || i < a) return;
        if (a == b) value = new_value;
        else {
            if (!l) l = new_tree();
            if (!r) r = new_tree();
            l->update(i, new_value, a, (a+b)/2);
            r->update(i, new_value, (a + b)/2 + 1, b);
            value = merge (l->value, r->value);
        }
    }

};
tree *new_tree() {
    static int bufsize = 1e7;
    static tree buf[(int) 1e7];
    assert(bufsize);
    return &buf[--bufsize];
}

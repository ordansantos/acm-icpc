#define N 4000000

struct node {
    int value;
    int lazy_value;
    bool lazy;

    node (int value = -1e8) : value(value), lazy_value(-1e8), lazy(false){} // change starting values

    node operator + (node other){  // change operator
        return node (min (value, other.value));
    }
};

node tree[4*N];

node NIL (N); // change NIL value

void dolazy (int v, int a, int b){ // change lazy
    if (tree[v].lazy){
        if (a != b){
            tree[v * 2].lazy = tree[v * 2 + 1].lazy = true;
            tree[v * 2].lazy_value = tree[v * 2 + 1].lazy_value = tree[v].lazy_value;
        }
        tree[v].lazy = false;
        tree[v].value = tree[v].lazy_value;
    }
}

node query(int i, int j, int v = 1, int a = 0, int b = N){
    dolazy(v, a, b);
    if (b < i || a > j) return NIL;
    if (a >= i && b <= j) return tree[v];
    return query(i, j, v * 2, a, (a + b)/2) + query(i, j, v * 2 + 1, (a + b)/2 + 1, b);
}

void update(int i, int j, int lazy_value, int v = 1, int a = 0, int b = N){
    dolazy(v, a, b);
    if (b < i || a > j) return;
    if (a >= i && b <= j){
        tree[v].lazy = true;
        tree[v].lazy_value = lazy_value;
        dolazy(v, a, b);
        return;
    }
    update(i, j, lazy_value, v * 2, a, (a + b)/2);
    update(i, j, lazy_value, v * 2 + 1, (a + b)/2 + 1, b);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}


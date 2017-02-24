struct ImplicitSegNode {

    int value;
    ImplicitSegNode *l, *r;

    ImplicitSegNode() : value(0), l(NULL), r(NULL) {}

    ~ImplicitSegNode() {
        delete l;
        delete r;
    }

    int query (int a, int b, int i, int j){
        if (i > b || j < a) return 0;
        if (a >= i && b <= j) return value;
        return (l? l->query(a, (a + b)/2, i, j) : 0) + (r? r->query((a + b)/2 + 1, b, i, j) : 0);
    }

    void update (int a, int b, int i, int value){
        if (i > b || i < a) return;
        if (a == b)
            this->value += value;
        else{
            if (!l) l = new ImplicitSegNode;
            if (!r) r = new ImplicitSegNode;
            l->update(a, (a+b)/2, i, value);
            r->update((a + b)/2 + 1, b, i, value);
            this->value = l->value + r->value;
        }
    }

};


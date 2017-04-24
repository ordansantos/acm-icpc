struct Treap{

    typedef struct _Node {

        ll x; int y; ll sum;
        ll value, _min;
        int cnt;
        _Node *l, *r;

        _Node (ll x) : x(x), y(((rand() << 16) ^ rand()) & 0x7fffffff), cnt(1), sum(x), value(x), _min(x), l(NULL), r(NULL){};
        ~_Node(){ };

        void recalc (){
            sum = value + sz(l) + sz(r);
            cnt = 1 + (l?l->cnt:0) + (r?r->cnt:0);
            _min = min ( {1LL*value, (l? l->_min:INF), (r? r->_min:INF)} );
        }

        ll sz (_Node *v){
            return v? v->sum : 0;
        }

    } *Node;

    void split (Node v, ll x, Node &l, Node &r){
        r = l = NULL;

        if (!v) return;

        if (v->x < x)
            l = v, split(v->r, x, v->r, r);
        else
            r = v, split(v->l, x, l, v->l);
        v->recalc();
    }

    Node merge (Node l, Node r){

        if (!l || !r){
            if (l) l->recalc();
            if (r) r->recalc();
            return l? l : r;
        }

        if (l->y > r->y){
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        } else{
            r->l = merge(l, r->l);
            r->recalc();
            return r;
        }
    }

    Node root;

    Treap() : root(NULL){}
    ~Treap(){ delete root; }

    void insert (ll x){
        Node l, r;
        split(root, x, l, r);
        root = merge(merge(l, new _Node(x)), r);
    }

    void erase (ll x){
        Node l, m, r, temp;
        split(root, x, l, m);
        split(m, x + 1, m, r);
        temp = m;
        m = merge(m->l, m->r);
        delete (temp);
        root = merge(l, merge(m, r));
    }

};

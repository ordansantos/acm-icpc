struct T {
    int value;
    // merge
    T operator + (const T &other) const{
        return min (value, other.value);
    }
    // nil
    T (int value = 1e9) : value(value){}
};

const int N = 500;

template <typename T>
struct SEG2D {
    // [1..N]
    T tree[4*N][4*N];
    T grid[N][N];

    // call set before build
    inline void set (int x, int y, T value){
        grid[x][y] = value;
    }

    inline void build2(int r, int c1, int c2, T *tree, int node = 1){
        if (c1 == c2)
            tree[node] = grid[r][c1]; // CHANGE THIS!
        else{
            build2(r, c1, (c1 + c2)/2, tree, node * 2);
            build2(r, (c1 + c2)/2+1, c2, tree, node * 2 + 1);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    inline void build3(int c1, int c2, T *tree, T *left, T *right, int node = 1){
        if (c1 == c2)
            tree[node] = left[node] + right[node];
        else{
            build3(c1, (c1 + c2)/2, tree, left, right, node * 2);
            build3((c1 + c2)/2+1, c2, tree, left, right, node * 2 + 1);
            tree[node] = left[node] + right[node];
        }
    }
    inline void build(int r1, int r2, int c1, int c2, int node = 1){
        if (r1 == r2)
            build2(r1, c1, c2, tree[node]);
        else{
            build (r1, (r1 + r2)/2, c1, c2, node * 2);
            build ((r1 + r2)/ 2 + 1, r2, c1, c2, node * 2 + 1);
            build3(c1, c2, tree[node], tree[node * 2], tree[node * 2 + 1]);
        }
    }


    inline T query2 (int c1, int c2, int qc1, int qc2, T *tree, int node = 1){
        if (qc2 < c1 || qc1 > c2) return T();
        if (c1 >= qc1 && c2 <= qc2) return tree[node];
        T q1 = query2(c1, (c1 + c2)/2, qc1, qc2, tree, node * 2);
        T q2 = query2((c1 + c2)/2 + 1, c2, qc1, qc2, tree, node * 2 + 1);
        return q1 + q2;
    }

    inline T query(int r1, int r2, int c1, int c2, int qr1, int qr2, int qc1, int qc2, int node = 1){
        if (qr2 < r1 || qr1 > r2) return T();
        if (r1 >= qr1 && r2 <= qr2) return query2(c1, c2, qc1, qc2, tree[node]);
        T q1 = query(r1, (r1 + r2)/2, c1, c2, qr1, qr2, qc1, qc2, node * 2);
        T q2 = query((r1 + r2)/2 + 1, r2, c1, c2, qr1, qr2, qc1, qc2, node * 2 + 1);
        return q1 + q2;
    }

    inline void update2 (int c1, int c2, int c, T value, T *tree, int node = 1){
        if (c < c1 || c > c2) return;
        if (c1 == c2){
            tree[node] = value; // CHANGE THIS!
            return;
        }
        update2(c1, (c1 + c2)/2, c, value, tree, node * 2);
        update2((c1 + c2)/2 + 1, c2, c, value, tree, node * 2 + 1);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    inline void update3 (int c1, int c2, int c, T *tree, T *left, T *right, int node = 1){
        if (c < c1 || c > c2) return;
        if (c1 == c2){
            tree[node] = left[node] + right[node];
            return;
        }
        update3(c1, (c1 + c2)/2, c, tree, left, right, node * 2);
        update3((c1 + c2)/2 + 1, c2, c, tree, left, right, node * 2 + 1);
        tree[node] = left[node] + right[node];
    }

    inline void update (int r1, int r2, int c1, int c2, int r, int c, T value, int node = 1){
        if (r < r1 || r > r2) return;
        if (r1 == r2){
            update2(c1, c2, c, value, tree[node]);
            return;
        }
        update(r1, (r1 + r2)/2, c1, c2, r, c, value, node * 2);
        update((r1 + r2)/2 + 1, r2, c1, c2, r, c, value, node * 2 + 1);
        update3(c1, c2, c, tree[node], tree[node * 2], tree[node * 2 + 1]);
    }
};


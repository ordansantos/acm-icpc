int v[100001], table[100001][21];
//[0,n)
void build(int n){
    for (int i = 0; i < n; i++) table[i][0] = v[i];
    for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
        table[i][j] = min (table[i][j-1], table[i+(1<<j-1)][j-1]);
}

int query (int l, int r, int table[N][LOG]){
    int log = __builtin_clz(1) - __builtin_clz(r-l+1);
    return min (table[l][log], table[r-(1<<log)+1][log]);
}

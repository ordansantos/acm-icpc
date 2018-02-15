
// use vector if possible
oset<int> bit[N];

void add (int x, int y){
	for (int idx = x; idx < N; idx += idx & -idx)
        bit[idx].insert(y);
}

int query (int x, int y){
	int sum = 0;
	for (int idx = x; idx; idx -= idx & -idx)
        sum += bit[idx].order_of_key(y + 1);
	return sum;
}

long long square (int x1, int y1, int x2, int y2){
    return query(x2, y2) - query(x2, y1-1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
}

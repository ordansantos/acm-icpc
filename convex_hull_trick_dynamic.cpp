#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T, typename cmp=less<T>> using oset =
tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
const double eps = 1e-9;
typedef long long ll;
struct Line{
    ll b, m;
    ll y (ll x){ return m*x + b; }
    double inter(Line other) const{ return 1.0*(other.b-b)/(m-other.m); }

    bool operator < (const Line &other) const {
        /// return m < other.m; /// FOR MAXIMUM
        return m > other.m;
    }

};
void add (oset <Line> &retas, ll m, ll b){
    Line r1;
    r1.m = m;
    r1.b = b;
    if (retas.find(r1) != retas.end()){
        auto r2 = *retas.find(r1);

        /// if (r2.b >= r1.b) return; /// FOR MAXIMUM
        if (r2.b <= r1.b) return;

        retas.erase(r2);
    }
    retas.insert(r1);
    while (true){
        auto it = retas.find(r1);
        auto a = it;
        auto b = ++it;
        if (b == retas.end()) break;
        auto c = ++it;
        if (c == retas.end()) break;
        if (c->inter(*a) < b->inter(*a) + eps) retas.erase(b);
        else break;
    }
    while (true){
        auto it = retas.find(r1);
        auto c = it;
        if (c == retas.begin()) break;
        auto b = --it;
        if (b == retas.begin()) break;
        auto a = --it;
        if (c->inter(*a) < b->inter(*a) + eps) retas.erase(b);
        else break;
    }
    while (retas.find(r1) != retas.end()){

        auto it = retas.find(r1);
        auto b = it;
        auto c = ++it;
        if (c == retas.end()) break;
        if (b == retas.begin()) break;
        auto a = --(--it);
        if (c->inter(*a) < b->inter(*a) + eps) retas.erase(b);
        else break;
    }

}

ll get_value(oset<Line> &retas, ll x){
    int l = 0, r = retas.size() - 1;
    while (l < r){
        int mid = (l + r) / 2;
        Line l1 = *retas.find_by_order(mid);
        Line l2 = *retas.find_by_order(mid + 1);
        double inter = l1.inter(l2);
        if (x > inter)
            l = mid + 1;
        else
            r = mid;
    }
    Line resp = *retas.find_by_order(l);
    return resp.y(x);
}

int main(){
    return 0;
}


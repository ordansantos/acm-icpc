#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T, typename cmp=less<T>> using oset =
tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

int main(){

    oset<int> s; // a pair can be used to simulate a multiset
    s.insert (10);
    s.insert (3);
    s.insert (18);
    cout << s.order_of_key (4) << endl ; // #elements less than x
    cout << *s.find_by_order (1) << endl; // get the iterator of the kth element
    return 0;
}


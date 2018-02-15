#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;
const int N = 100005;

ll fastpow (ll n, ll p){
    if (p == 0) return 1;
    if (p % 2) return n * fastpow(n, p - 1) % MOD;
    ll aux = fastpow(n, p / 2);
    return aux * aux % MOD;
}

ll fat[N], inv_fat[N];

void build (){
    if (fat[0] == 1) return;
    fat[0] = 1;
    for (int i = 1; i < N; i++)
        fat[i] = fat[i - 1] * i % MOD;
    for (int i = 0; i < N; i++)
        inv_fat[i] = fastpow(fat[i], MOD - 2);
}
// n!/(n-m)!/m!
ll comb (ll n, ll m){
    build();
    return fat[n] * inv_fat[m] % MOD * inv_fat[n - m] % MOD;
}

int main(){

    return 0;
}


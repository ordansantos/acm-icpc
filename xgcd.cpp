ll xgcd (ll a, ll b, ll &x, ll &y){
    if (b == 0){
        x = 1, y = 0;
        return a;
    }
    ll x1, y1, g = xgcd (b, a%b, x1, y1);
    x = y1, y = x1 - a/b * y1;
    return g;
}

// ax + by = gcd (a, b)
// a * x0 * (n/gcd(a,b)) + b * y0 * (n/gcd(a,b)) = n
// a * (x + b/gcd(a,b) * k) + b * (y - a/gcd(a,b) * k) = n
// a * (x - b/gcd(a,b) * k) + b * (y + a/gcd(a,b) * k) = n


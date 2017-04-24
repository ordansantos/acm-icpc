#include <bits/stdc++.h>

using namespace std;

typedef long long T;
const double eps = 1e-9;

bool doubleEquals (T a, T b){ return abs(a - b) < eps; }

struct Point{
    T x, y;
    Point(){}
    Point (T x, T y) : x(x), y(y){}
    Point operator - (Point &p) { return Point (x - p.x, y - p.y); }
    Point operator + (Point &p){ return Point (x + p.x, y + p.y); }
    bool operator < (const Point &p) const{ return x < p.x || (x == p.x && y < p.y); }
    bool operator == (Point p){ return doubleEquals(x, p.x) && doubleEquals(y, p.y); }
};

T cross(Point O, Point A, Point B){
    return (A - O).x * (B - O).y - (A - O).y * (B - O).x;
}

vector <Point> convexHull (vector <Point> &points){
    vector <Point> hull(points.size()+1);
    int k = 0;
    sort (points.begin(), points.end());
    for (int i = 0; i < points.size(); i++){
        while (k >= 2 && (cross(hull[k-2], hull[k-1], points[i]) + eps > 0)) k--;
        hull[k++] = points[i];
    }
    for (int i = points.size() - 2, t = k + 1; i >= 0; i--){
        while (k >= t && cross(hull[k-2], hull[k-1], points[i]) + eps > 0) k--;
        hull[k++] = points[i];
    }
	k--;
    hull.resize(k);
    return hull;
}

bool insideTriangle (Point A, Point B, Point C, Point p){
    return abs(cross(p, A, B)) + abs(cross(p, B, C)) + abs(cross(p, C, A)) == abs(cross(p, A, B) + cross(p, B, C) + cross(p, C, A));
}

Point pivot;

bool cmp (const Point &A, const Point &B){
    return cross(pivot, A, B) > 0;
}

void prepare (vector<Point> &convex){
    for (int i = 1; i < convex.size(); i++)
        if (convex[i] < convex[0]) swap(convex[i], convex[0]);
    pivot = convex[0];
    sort(convex.begin() + 1, convex.end(), cmp);
}

bool isInside (vector<Point> &convex, Point p){
    int l = 0, r = convex.size() - 1;
    while (l < r){
        int mid = (l + r + 1) / 2;
        if (cross(convex[0], convex[mid], p) >= 0)
            l = mid;
        else
            r = mid - 1;
    }
    return insideTriangle(convex[0], convex[l], convex[l + 1 != convex.size()? l + 1: l - 1], p);
}

int main(){

    int n;

    while (scanf ("%d", &n) != EOF){
        vector <Point> large;
        for (int i = 0; i < n; i++){
            int a, b;
            scanf ("%d %d", &a, &b);
            large.push_back({a, b});
        }
        vector<Point> convex = convexHull(large);
        prepare(convex);
        vector<Point> small;
        scanf ("%d", &n);
        for (int i = 0; i < n; i++){
            int a, b;
            scanf ("%d %d", &a, &b);
            small.push_back({a, b});
        }
        int q = 0;
        for (auto p : small)
            q += isInside(convex, p);
        printf ("%d\n", q);

    }

    return 0;
}


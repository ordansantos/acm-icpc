#include <bits/stdc++.h>

using namespace std;

typedef long double T;
const T eps = 1e-10;

bool doubleEquals (T a, T b){ return abs(a - b) < eps; }

struct Point{
    T x, y;
    Point(){}
    Point (T x, T y) : x(x), y(y){}
    Point operator - (Point p) { return Point (x - p.x, y - p.y); }
    Point operator + (Point p){ return Point (x + p.x, y + p.y); }
    Point operator / (T e) { return Point (x / e, y / e); }
    Point operator * (T e) { return Point (x * e, y * e); }
};

T cross(Point O, Point A, Point B){
    return (A - O).x * (B - O).y - (A - O).y * (B - O).x;
}

T dot(Point A, Point B){
    return A.x * B.x + A.y * B.y;
}

T dist(Point A, Point B){
    return sqrtl(dot(A-B, A-B));
}


pair<Point, Point> centerCircle (Point a, Point b, T r){
    Point c = (a + b) / 2;
    T d = dist(a, b);
    Point v = (b - a)/d;
    swap(v.x, v.y);
    v.x *= -1;
    T q;
    if (doubleEquals(r * r, (d/2) * (d/2)))
        q = 0;
    else
        q = sqrt (r * r - (d/2) * (d/2));
    return {c + (v * q), c - (v * q)};
}

T getAxisAngle (Point c, Point p){
    T ang = atan2((p-c).y, (p-c).x);
    if (ang < 0) ang += 2 * acos(-1.0);
    return ang;
}

struct evento {
    int type, id;
    T rad;
    bool operator < (const evento &other) const{
        if (rad + eps < other.rad) return true;
        if (other.rad + eps < rad) return false;
        return type > other.type;
    }
};

// 2 * #pontos + 10 :P
bool ativos[5000];

// center is in position 0
int sweepAngle (vector <Point> &points, T raio){
    Point c = points[0];
    vector <evento> eventos;
    int id = 0;
    for (int i = 1; i < points.size(); i++){
        Point p = points[i];
        Point a, b;
        if (dist(c, p) > 2 * raio + eps) continue;
        tie(a, b) = centerCircle(c, p, raio);
        if (cross(c, a, b) < 0) swap (a, b);
        evento st, fi;
        st.rad = getAxisAngle(c, a);
        st.type = 1;
        fi.rad = getAxisAngle(c, b);
        fi.type = 0;
        fi.id = st.id = id++;
        eventos.push_back(st);
        eventos.push_back(fi);
    }
    sort (eventos.begin(), eventos.end());
    memset(ativos, false, sizeof ativos);
    int ans = 0, qtd = 0;
    for (int i = 0; i < 2 * eventos.size(); i++){
        int j = i % eventos.size();
        if (eventos[j].type == 0){
            if (ativos[eventos[j].id])
                ativos[eventos[j].id] = false, qtd--;
        } else
            ativos[eventos[j].id] = true, qtd++;
        ans = max (qtd, ans);
    }
    return ans + 1;
}

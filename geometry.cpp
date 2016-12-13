#include <bits/stdc++.h>

using namespace std;

typedef double T;
const double eps = 1e-10; // -9 is dangerous

bool doubleEquals (T a, T b){ return abs(a - b) < eps; }

struct Point{
    T x, y;
    Point(){}
    Point (T x, T y) : x(x), y(y){}
    Point operator - (Point p) { return Point (x - p.x, y - p.y); }
    Point operator + (Point p){ return Point (x + p.x, y + p.y); }
    Point operator / (T e) { return Point (x / e, y / e); }
    Point operator * (T e) { return Point (x * e, y * e); }
    bool operator < (const Point &p) const{ return x < p.x || (x == p.x && y < p.y); }
    bool operator == (Point p){ return doubleEquals(x, p.x) && doubleEquals(y, p.y); }
};

ostream& operator<<(ostream& os, Point p) {
    return os << "(" << p.x << "," << p.y << ")";
}

T cross(Point O, Point A, Point B){
    return (A - O).x * (B - O).y - (A - O).y * (B - O).x;
}

T dot(Point A, Point B){
    return A.x * B.x + A.y * B.y;
}

T dist(Point A, Point B){
    return sqrtl(dot(A-B, A-B));
}

double distLine(Point A, Point B, Point P){
    return abs(cross(A, B, P) / dist(A, B));
}

double angle(Point O, Point A, Point B){
    return acos(dot(A-O, B-O)/(dist(O, A)*dist(O, B)));
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

/*
Bottom, left: inside
Top, right: outside
*/
bool pnpoly(Point p, vector <Point> &points){
  bool c = 0;
  for (int i = 0, j = points.size()-1; i < points.size(); j = i++) {
    if ( ((points[i].y > p.y) != (points[j].y > p.y)) &&
     (p.x < (double)(points[j].x-points[i].x) * (p.y-points[i].y) / (points[j].y-points[i].y) + points[i].x) )
       c = !c;
  }
  return c;
}

// Ax + By + c = 0
struct Line{
    T A, B, C;
    Line (T A, T B, T C) : A(A), B(B), C(C){};
    Line(Point p1, Point p2){
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = p1.x*p2.y-p1.y*p2.x;
    }

    bool parallel(Line l){
        return doubleEquals(B*l.A - A*l.B, 0);
    }

    bool equals(Line l){
        if (!parallel(l)) return false;
        return parallel(l) && doubleEquals(distLine(l), 0);
    }

    Point inter(Line l){
        assert(!parallel(l));
        Point ret;
        ret.x = (l.C*B-C*l.B)/(l.B*A-B*l.A);
        ret.y = (l.C*A-C*l.A)/(B*l.A-l.B*A);
        return ret;
    }

    double distLine(Line l){
        if (l.A == 0) return distPoint({0, -l.C/l.B});
        return distPoint({-l.C/l.A, 0});
    }

    double distPoint(Point p){
        return abs(A*p.x + B*p.y+C)/sqrt(A*A+B*B);
    }

    // that touches a point p
    Line getPerpendicular(Point p){
        Line l(B, -A, 0);
        l.C = -l.A*p.x - l.B*p.y;
        return l;
    }
};

bool pointInSegment(pair<Point, Point> s, Point p){
	if (doubleEquals (cross(s.first, s.second, p), 0)){
    	T xa = min (s.first.x, s.second.x), xb = max(s.first.x, s.second.x);
    	T ya = min (s.first.y, s.second.y), yb = max(s.first.y, s.second.y);
    	return p.x + eps > xa && p.x - eps < xb && p.y + eps > ya && p.y - eps < yb;
	}
	return false;
}

bool segmentInter(pair<Point, Point> A, pair<Point, Point> B){
    Line la(A.first, A.second), lb(B.first, B.second);
    if (la.parallel(lb) && !la.equals(lb)) return false;
    if (la.equals(lb)){
        if (max(A.first.x, A.second.x) + eps < min(B.first.x, B.second.x)) return false;
        if (min(A.first.x, A.second.x) - eps > max(B.first.x, B.second.x)) return false;
        if (max(A.first.y, A.second.y) + eps < min(B.first.y, B.second.y)) return false;
        if (min(A.first.y, A.second.y) - eps > max(B.first.y, B.second.y)) return false;
        return true;
    }
    Point i = la.inter(lb);
    return pointInSegment(A, i) && pointInSegment(B, i);
}

double distSegmentToPoint(pair<Point, Point> s, Point P){
    if (dot(s.first-s.second, P-s.second) < 0) return dist(s.second, P);
    if (dot(s.second-s.first, P-s.first) < 0) return dist(s.first, P);
    return distLine(s.first, s.second, P);
}

double distSegmentToSegment(pair<Point, Point> sa, pair<Point, Point> sb){
    if (sa.first == sa.second && sb.first == sb.second) return dist(sa.first, sb.first); // only a point
    if (sa.first == sa.second) return distSegmentToPoint(sb, sa.first);
    if (sb.first == sb.second) return distSegmentToPoint(sa, sb.first);
    if (segmentInter(sa, sb)) return 0;
    return min({distSegmentToPoint(sa, sb.first), distSegmentToPoint(sa, sb.second),
                distSegmentToPoint(sb, sa.first), distSegmentToPoint(sb, sa.second)});
}

double polygonArea(vector <Point> &points){
	double area = 0;
	for (int i = 0; i < points.size(); i++)
		area += cross({0, 0}, points[i], points[(i+1)%points.size()]);
	return abs(area)/2.0;
}

Point rotate (Point O, Point p, double rad){
    p = p - O;
    T x = p.x * cos(rad) + p.y * -sin(rad);
    T y = p.x * sin(rad) + p.y * cos(rad);
    return Point(x, y) + O;
}

// check this for double!!!
bool insideTriangle (Point A, Point B, Point C, Point p){
    return abs(cross(p, A, B)) + abs(cross(p, B, C)) + abs(cross(p, C, A)) == abs(cross(p, A, B) + cross(p, B, C) + cross(p, C, A));
}

pair<Point, Point> centerCircle (Point a, Point b, T r){
    Point c = (a + b) / 2;
    double d = dist(a, b);
    Point v = (b - a)/d;
    swap(v.x, v.y);
    v.x *= -1;
    assert (d < 2 * r + eps);
    double q;
    if (doubleEquals(r * r, (d/2) * (d/2)))
        q = 0;
    else
        q = sqrt (r * r - (d/2) * (d/2));
    return { c + (v * q), c - (v * q)};
}

double getAxisAngle (Point c, Point p){
    double ang = atan2((p-c).y, (p-c).x);
    if (ang < 0) ang += 2 * acos(-1);
    return ang;
}



struct Circle{
    Point p;
    T r;
    Circle(Point p, T r) : p(p), r(r){}
    bool touch(Circle other){
        double d = dist(p, other.p);
        return d < r + other.r + eps;
    }

    // a inside b not implies b inside a
    bool inside(Circle other){
        double d = dist(p, other.p);
        return d + r < other.r - eps;
    }

    bool cover(Point point){
        return dist(point, p) < r + eps;
    }

    bool equal(Circle other){
        double d = dist(p, other.p);
        return doubleEquals(d, 0) && doubleEquals(r, other.r);
    }

};

pair <Point, Point> circleIntersection(Circle c1, Circle c2){
    assert (c1.touch(c2));
    assert (!c1.inside(c2) && !c2.inside(c1));
    assert (!c1.equal(c2));

    T d = dist(c1.p, c2.p);
    T a = (c1.r*c1.r-c2.r*c2.r+d*d)/(2*d);
    T h = sqrtl (c1.r*c1.r-a*a);
    Point u = (c2.p - c1.p)/d;
    Point pu = Point(-u.y, u.x);
    u = u * a;
    pu = pu * h;
    return {u+pu+c1.p, u-pu+c1.p};
}

int main(){

    // Circle
    assert (Circle({3, 4}, 5).inside(Circle({4, 5}, 7)));
    assert (!Circle({0, 0}, 2).inside(Circle({1, 0}, 1)));
    assert (Circle({0, 0}, 2).touch(Circle({1, 0}, 1)));
    assert (Circle({0, 0}, 2).touch(Circle({2.5, 0}, 1)));
    assert (!Circle({0, 0}, 2).touch(Circle({10, 0}, 1)));
    assert (Circle({0, 0}, 2).equal(Circle({0, 0}, 2)));

    pair<Point, Point> inter = circleIntersection(Circle({0, 0}, 2), Circle({4, 0}, 2));
    assert(doubleEquals(inter.first.x, 2.));
    assert(doubleEquals(inter.first.y, 0.));
    assert(doubleEquals(inter.second.x, 2.));
    assert(doubleEquals(inter.second.y, 0.));

    inter = circleIntersection(Circle({-3.5, 7}, 3), Circle({2, 6}, 4));

    assert(doubleEquals(inter.first.x, -0.99524940998024));
    assert(doubleEquals(inter.first.y, 8.6511282451087));
    assert(doubleEquals(inter.second.x,  -1.7367505900198));
    assert(doubleEquals(inter.second.y, 4.5728717548913));
    assert(Circle({0, 0}, 3).cover(Point(0, 3)));
    assert(!Circle({0, 0}, 3).cover(Point(0, 3.001)));
    assert(Circle({0, 0}, 3).cover(Point(0, 2)));
    // Circle

    return 0;
}




#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);
typedef double T;
using ll = long long;

struct Point {
  T x;
  T y;
  Point(T _x, T _y): x(_x), y(_y) {}
  Point(): x(0.0), y(0.0) {}

  bool operator < (Point other) const {
    if (fabs(x - other.x) > EPS) 
      return x < other.x;
    return y < other.y;
  }

  bool operator == (Point other) const {
    return (
      fabs(x - other.x) < EPS && 
      fabs(y - other.y) < EPS
    );
  }

  bool operator != (Point other) const {
    return !(*this == other);
  }

  bool operator += (Point other) {
    x += other.x;
    y += other.y;
    return true;
  }

  bool operator /= (T d) {
    x /= d; 
    y /= d;
    return true;
  }

  static T hypot(T dx, T dy) {
    return sqrt(dx*dx + dy*dy);
  } 

  static ll sqhypot(ll dx, ll dy) {
    return dx*dx + dy*dy;
  } 

  T dist(Point other) {
    return hypot(x - other.x, y - other.y);
  }

  ll sqdist(Point other) {
    return sqhypot(x - other.x, y - other.y);
  }

  static T abs(Point other) {
    return hypot(other.x, other.y);
  }
  
  static T sq(Point other) {
    return other.x*other.x + other.y*other.y;
  }

  int coordinatesValue() {
    T z = x*y;
    if (z<0) return -1;
    else if (z>0) return 1;
    else return 0;
  }

  Point operator + (Point p) { 
    return {x+p.x, y+p.y}; 
  }

  Point operator - (Point p) { 
    return {x-p.x, y-p.y}; 
  }

  Point operator * (T d) { 
    return {x*d, y*d}; 
  }

  Point operator / (T d) { 
    return {x/d, y/d}; 
  }

  Point& translate(Point other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Point& scale(Point other, T factor) {
    *this = other + (*this - other)*factor; 
    return *this;
  }

  Point& rotate(T a) {
    T _x = x;
    T _y = y;
    x = _x*cos(a) - y*sin(a);
    y = _x*sin(a) + y*cos(a);
    return *this;
  }

  T dot(Point w) {
    return x*w.x + y*w.y;
  }

  static T dot(Point v, Point w) {
    return v.x*w.x + v.y*w.y;
  }

  bool isPerp(Point w) {
    return dot(w) == 0;
  }

  static Point perp(Point p) {
    return Point(-p.y, p.x);
  }

  T angle(Point w) {
    double cosTheta = 
      dot(w) / 
        Point::abs(*this) / Point::abs(w);

    return 
      acos(max(-1.0, min(1.0, cosTheta)));
  }

  static bool angleLess(
    Point a1, Point b1, 
    Point a2, Point b2) {

    Point p1(a1.dot(b1), fabs(a1.cross(b1)));
    Point p2(a2.dot(b2), fabs(a2.cross(b2)));

    return p1.cross(p2) > 0.0;
  }

  T cross(Point w) {
    return x*w.y - y*w.x;
  }
  
  static T cross(Point v, Point w) {
    return v.x*w.y - v.y*w.x;
  }

  static T orientation(
    Point a, Point b, Point c) {

    return Point::cross(b-a, c-a);
  }

  static bool inAngle(
    Point a, Point b, Point c, Point p) {

    if (Point::orientation(a,b,c) < 0) 
      swap(b, c);
    return Point::orientation(a, b , p) >= 0 
      && Point::orientation(a, c, p) <= 0;
  }

  static bool isConvex(vector<Point> Points){
    bool hasPos = false, hasNeg = false;
    for (int i=0,n=Points.size(); i<n; i++) {
      int o = Point::orientation(
        Points[i], 
        Points[(i+1)%n], 
        Points[(i+2)%n]
      );
      hasPos |= (o>0);
      hasNeg |= (o<0);
    }
    return !(hasPos && hasNeg);
  }

  bool half() {
    assert(x != 0 || y != 0);
    return y>0.0 || (y == 0.0 && x < 0.0);
  }
};



void polarSort(vector<Point> &v) {
  sort(v.begin(), v.end(), [](
    Point v, Point w
    ){
    return 
    make_tuple(v.half(), 0, Point::abs(v)) < 
    make_tuple(w.half(),
              Point::cross(v, w), 
              Point::abs(w));
  }); 
}

void polarSortAround(
  Point o, vector<Point> &v
  ) 
{
  sort(v.begin(), v.end(), [=](
    Point v, Point w
    ) {
    return make_tuple(Point(v-o).half(), 0)< 
          make_tuple(Point(w-o).half(), 
          Point::cross(v-o, w-o));
  });
};


struct Line {
  Point v;
  T c;

  Line(Point v, T c): v(v), c(c) {}
  Line(T a, T b, T c): 
    v(Point(b, -a)), c(c) {}
  Line(Point p, Point q): 
    v(q-p), c(Point::cross(v, p)) {}

  T side(Point p) {
    return Point::cross(v, p) - c;
  }

  T dist(Point p) {
    return abs(side(p)) / Point::abs(v);
  }

  Line perpThrough(Point p) {
    return Line(p, p+Point::perp(v));
  }

  // return true if p appears before
  // than q in the Line
  bool cmpProj(Point p, Point q) {
    return Point::dot(v, p) <
          Point::dot(v, q);
  }

  Line& translate(Point t) {
    *this = Line(v, c+Point::cross(v, t));
    return *this;
  }

  Line& shiftLeft(T dist) {
    *this = Line(v, c+dist*Point::abs(v));
    return *this;
  }

  static bool intersection(
    Line l1, Line l2, Point &out
    ) {
    T d = Point::cross(l1.v, l2.v);
    if (d==0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d;
    return true;
  }

  Point proj(Point p) {
    return p - 
      Point::perp(v)*side(p)/Point::sq(v);
  }

  Point refl(Point p) {
    return 
    p - 
    Point::perp(v)*2.0*side(p)/Point::sq(v);
  }

  Line bisector(
    Line l1, Line l2, bool interior
    ) {
    assert(Point::cross(l1.v, l2.v) != 0);
    T sign = interior ? 1.0 : -1.0;
    return 
    Line(l2.v/Point::abs(l2.v) + 
          l1.v/Point::abs(l1.v) * sign,
        l2.c/Point::abs(l2.v) + 
          l1.c/Point::abs(l1.v) * sign);
  }

};

bool onDisk(Point a, Point b, Point c) {
  return Point::dot(a-c, b-c) <= 0;
}

bool onSegment(Point a, Point b, Point p) {
  return Point::orientation(a, b, p) == 0 
        && onDisk(a, b, p);
}

bool properIntersection(
  Point a, Point b, Point c, Point d, 
  Point &out) {
  double oa = Point::orientation(c, d , a),
        ob = Point::orientation(c,d,b),
        oc = Point::orientation(a,b,c),
        od = Point::orientation(a,b,d);
  // Proper inter exists iff opposite signs
  if (oa*ob < 0.0 && oc*od < 0.0) {
    out = Point(a*ob - b*oa)/(ob-oa);
    return true;
  } 
  return false;
}

bool singleIntersection(
  Point a, Point b, Point c, Point d, 
  Point &out) {
  if (properIntersection(a,b,c,d,out)) {
    return true;
  }
  if (onSegment(c,d,a)) {
    out = a;
    return true;
  }
  if (onSegment(c,d,b)) {
    out = b;
    return true;
  }
  if (onSegment(a,b,c)) {
    out = c;
    return true;
  }
  if (onSegment(a,b,d)) {
    out = d;
    return true;
  }
  return false;
}

T segmentPointDist(
  Point a, Point b, Point p
  ) {
  if (a != b) {
    Line line(a, b);
    if (line.cmpProj(a, p) 
        && line.cmpProj(p, b)) {
      return line.dist(p);
    }
  } 
  return min(Point::abs(p-a), 
            Point::abs(p-b));
}

T segmentSegmentDistance(
  Point a, Point b, Point c, Point d
  ) {
  Point dummy;
  if (properIntersection(a, b, c, d, dummy)){
    return 0.0;
  }
  return min({
    segmentPointDist(a,b,c),
    segmentPointDist(a,b,d),
    segmentPointDist(c,d,a),
    segmentPointDist(c,d,b)
  });
}

T areaTriangle(Point a, Point b, Point c) {
  return abs(Point::cross(b-a, c-a))/2.0;
}

T areaPolygon(vector<Point> pts) {
  T area = 0.0;
  for (int i=0,n=pts.size();i<n;i++) {
    area+=Point::cross(pts[i],pts[(i+1)%n]);
  }
  return abs(area) / 2.0;
} 

ll areaPolygonLong(vector<Point> pts) {
  ll area = 0;
  for (int i=0,n=pts.size();i<n;i++) {
    area += (ll)pts[i].x*(ll)pts[(i+1)%n].y;
    area -= (ll)pts[i].y*(ll)pts[(i+1)%n].x;  
  }
  return abs(area);
}

bool above(Point a, Point p) {
  return p.y >= a.y;
}

bool crossesRay(Point a, Point p, Point q) {
  return (above(a,q) - above(a,p)) * 
          Point::orientation(a,p,q)>0;
}

// strict=1, return false when A on boundary
bool inPolygon(
  vector<Point> pts, Point A, 
  bool strict = true
  ) {
  int numCrossings = 0;
  for (int i=0,n=pts.size();i<n;i++) {
    if (onSegment(pts[i],pts[(i+1)%n], A)) {
      return !strict;
    }
    numCrossings += 
      crossesRay(A,pts[i],pts[(i+1)%n]);
  }
  return numCrossings & 1;
}

ll pointsBoundary(vector<Point> &pts) {
  ll boundary = 0;
  int n = (int)pts.size();
  for (int i=0;i<n;i++) {
    if (pts[(i+1)%n].x == pts[i].x) 
      boundary += 
        abs((ll)pts[(i+1)%n].y-(ll)pts[i].y);
    else if (pts[(i+1)%n].y == pts[i].y)
      boundary += 
        abs((ll)pts[(i+1)%n].x-(ll)pts[i].x);
    else boundary += __gcd(
      abs((ll)pts[(i+1)%n].x - (ll)pts[i].x),
      abs((ll)pts[(i+1)%n].y - (ll)pts[i].y)
    );
  }
  return boundary;
}

pair<ll,ll> latticePoints(vector<Point> ps) {
  ll area = areaPolygonLong(ps);
  ll boundary = pointsBoundary(ps);
  ll interior = (area+2ll-boundary)/2ll;
  return {interior, boundary};
}
struct Circle {
  static Point circumCenter(
    Point a, Point b, Point c
    ) {
    b = b-a;
    c = c-a;
    assert(Point::cross(b, c) != 0);
    return a +
    Point::perp(b*Point::sq(c) -
    c*Point::sq(b))/Point::cross(b,c)/2.0;
  }
};

T deg2rad(T angle) {
  angle *= 2.0*PI/360.0;
  return angle;
}

T rad2deg(T angle) {
  angle *= 360.0/(2.0*PI);
  return angle;
}

ll minDistancePoints(vector<Point> pts) {
  sort(pts.begin(), pts.end());
  ll minDistance = LLONG_MAX;
  set<Point> active; 
  active.insert({pts[0].y, pts[0].x});
  int j = 0;
  for (int i=1;i<pts.size();i++) {
    auto it = active.begin();
    ll dd = ceil(sqrt(minDistance));
    while (j<i && pts[j].x < pts[i].x-dd) {
      active.erase({pts[j].y, pts[j].x});
      j++;
    }
    auto lb = active.lower_bound({
      pts[i].y - dd, 0
    });
    auto ub = active.upper_bound({
      pts[i].y + dd, 0
    });

    for (auto it = lb; it != ub;it++) {
      minDistance = min(
        minDistance,
        Point(it->y,it->x).sqdist(pts[i])
      );
    }
    active.insert({pts[i].y, pts[i].x});
  }
  return minDistance;
}

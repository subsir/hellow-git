#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

using namespace std; 

const double EPS = 1e-9;
struct point {
    double x, y;
    point operator+(point rhs) const {
        return (point){x + rhs.x, y + rhs.y};
    }
    point operator-(point rhs) const {
        return (point){x - rhs.x, y - rhs.y};
    }
    point operator*(double rhs) const {
        return (point){x * rhs, y * rhs};
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
};
int sgn(double x) {
    if (x < -EPS) return -1;
    if (x > EPS) return 1;
    return 0;
}
double det(point x, point y) {
    return x.x * y.y - x.y * y.x;
}
double dot(point x, point y) {
    return x.x * y.x + x.y * y.y;
}
double dis(point x, point y) {
    return (x - y).len();
}
struct circle {
    point c;
    double r;
};
bool in_circle(point p, circle c) {
    return sgn(c.r - (c.c - p).len()) >= 0;
}
circle make_circle(point x, point y) {
    return (circle){(x + y) * 0.5, (x - y).len() * 0.5};
}
circle make_circle(point x, point y, point z) {
    point p = y - x, q = z - x, s = (point){dot(p, p) * 0.5, dot(q, q) * 0.5};
    double d = 1.0 / det(p, q);
    p = (point){det(s, (point){p.y, q.y}), det((point){p.x, q.x}, s)} * d;
    return (circle){x + p, p.len()};
}

bool Inline(point p1, point p2, point p3) {
  if ((p1.x - p3.x) * (p2.y - p3.y) == (p2.x - p3.x) * (p1.y - p3.y)) {
    return true;
  }
  return false;
}

bool Obtuse(point p1, point p2, point p3) {
  if ((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y) < 0) {
    return true;
  }
  if ((p2.x - p3.x) * (p1.x - p3.x) + (p2.y - p3.y) * (p1.y - p3.y) < 0) {
    return true;
  }
  if ((p1.x - p2.x) * (p3.x - p2.x) + (p1.y - p2.y) * (p3.y - p2.y) < 0) {
    return true;
  }
  return false;
}
int n;
double ans;
vector<point> p;
circle o;
point now[3];

circle Make(point x, point y, point z) {
  if (Inline(x, y, z)) {
    if ((x.x - y.x) * (x.x - z.x) < 0) {
      return make_circle(z, y);
    }
    if ((y.x - x.x) * (y.x - z.x) < 0) {
      return make_circle(z, x);
    }
    if ((z.x - x.x) * (z.x - y.x) < 0) {
      return make_circle(x, y);
    }
  }
  return make_circle(x, y, z);
}

bool check(int x, circle c) {
  for (int i = 0; i < x; i++) {
    if (in_circle(p[i], c) == false) {
      return false;
    }
  }
  return true;
}

void Input(int x) {
  if (x == n) {
    ans = min(ans, o.r);
    return;
  }
  point temp = p[x];
  if (in_circle(temp, o)) {
    Input(x + 1);
  } else {
    circle o1 = Make(now[0], now[1], temp);
    circle o2 = Make(now[1], now[2], temp);
    circle o3 = Make(now[2], now[0], temp);
    bool check1 = check(x, o1);
    bool check2 = check(x, o2);
    bool check3 = check(x, o3);
    circle oo = o;
    if (check1) {
      point temp1 = now[2];
      now[2] = temp;
      o = o1;
      Input(x + 1);
      now[2] = temp1;
      o = oo;
    }
    if (check2) {
      point temp1 = now[0];
      now[0] = temp;
      o = o2;
      Input(x + 1);
      now[0] = temp1;
      o = oo; 
    }
    if (check3) {
      point temp1 = now[1];
      now[1] = temp;
      o = o3;
      Input(x + 1);
      now[1] = temp1;
      o = oo;
    }
  }
}



int main() {
  double x, y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    p.push_back({point{x, y}});
  }
  o = make_circle(p[0], p[1]);  
  ans = 1e10;
  Input(2);
  cout << ans << endl;
}
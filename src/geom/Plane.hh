#ifndef PLANE_HH_
#define PLANE_HH_

#include <iostream>

class Plane {

private:
  double a,b,c,d;

public:

  Plane(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

  friend std::ostream& operator <<(std::ostream& s, const Plane& p) {
    return s << p.a << "x + " << p.b << "y + " << p.c << "z + " << p.d;
  }
#if 0
  Vec3d intersect(Line L) { /*  comment */
    return Vec3d(1,2,3);
  }
#endif
};

#endif
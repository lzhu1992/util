/* 
 * File:   Cube.hh
 * Author: Julia
 *
 * Created on May 25, 2017, 4:18 PM
 */

#ifndef CUBE_HH
#define CUBE_HH
#include <iostream>
#include <cmath>
using namespace std;
namespace geom {
class Cube {
public:
    double x1,y1,z1,x2,y2,z2;
    Cube(double x1, double y1, double z1, double x2, double y2, double z2) : 
    x1(x1), y1(y1), z1(z1), x2(x2), y2(y2),z2(z2) {
    }
    Cube(double x, double y, double z, double r):x1(x),y1(y),z1(z),x2(x+r),y2(y+r),z2(z+r){
    }
    double volume() const {
        return abs(x1-x2)*abs(y1-y2)*abs(z1-z2);
    }
    double area() const {

            return 2*abs(x1-x2)*abs(y1-y2)+2*abs(y1-y2)*abs(z1-z2)+2*abs(x1-x2)*abs(z1-z2);
    }
    friend ostream& operator <<(ostream& s, const Cube& c) {
            return s << '(' << c.x1 << ',' << c.y1 << ',' << c.z1 << ',' << c.x2 << ',' << c.y2 << ',' << c.z2 << ')';
    }
};
};


#endif /* CUBE_HH */


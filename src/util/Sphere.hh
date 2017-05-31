/* 
 * File:   Sphere.hh
 * Author: Julia
 *
 * Created on May 30, 2017, 11:15 AM
 */

#ifndef SPHERE_HH
#define SPHERE_HH
#include <iostream>
#include <cmath>
using namespace std;
namespace geom {
class Sphere {
public:
	double x,y,z,r;
	Sphere(double x, double y, double z, double r) : x(x), y(y), z(z), r(r) {
	}
        //TODO: Polyhedron
	//Polyhedron approxPolyhedron(int quality);
	double volume() const {
		return 4.0/3*M_PI * r*r*r;
	}
	double area() const {
		return 4 * M_PI * r*r;
	}
	Cube boundingCube() const {
		return Cube(x,y,z,r*2);
	}
        friend ostream& operator <<(ostream& s, const Sphere& c) {
		return s << '(' << c.x << ',' << c.y << ',' << c.z << ',' << c.r  << ')';
	}
};
};
	

#endif /* SPHERE_HH */


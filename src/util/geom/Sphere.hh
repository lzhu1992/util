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
#include "Cube.hh"

namespace geom {
class Sphere {
public:
        const double PI= 3.14159265358979323846;
	double x,y,z,r;	//origin:x, y, z AND radius: r
        //constructor takes in center point and radius
	Sphere(double x, double y, double z, double r) : x(x), y(y), z(z), r(r) {
	}
        //TODO: Polyhedron
	//Polyhedron approxPolyhedron(int quality);
	double volume() const {
		return 4.0/3* PI * r*r*r;
	}
	double area() const {
		return 4 * PI * r*r;
	}
	Cube boundingCube() const {
		return Cube(x,y,z,r*2);
	}
        friend std::ostream& operator <<(std::ostream& s, const Sphere& c) {
		return s << '(' << c.x << ',' << c.y << ',' << c.z << ',' << c.r  << ')';
	}
};
};
	

#endif /* SPHERE_HH */


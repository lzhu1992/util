#ifndef VEC3D_HH_
#define VEC3D_HH_

#include <iostream>
#include <cmath>
#include "Sphere.hh"
#include "Cube.hh"
#include "Plane.hh"

namespace geom {

class Vec3d {
public:
  double x,y,z;
  /*Vec3d(string a, string b, string c) {
 +  		// added by David Kim (to help with converting string to Vec3d)
 +  		x = stod(a);
 +		y = stod(b);
 +		z = stod(c);
 +  	}*/
  //constructor takes in 3 doubles
  Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}
  friend Vec3d operator +(const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x+b.x, a.y+b.y, a.z+b.z);
  }
  friend Vec3d operator -(const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x-b.x, a.y-b.y, a.z-b.z);
  }
  Vec3d add(double a) const {
    return Vec3d(x+a,y+a,z+a); 
  }
  Vec3d sub(double a) const {
    return Vec3d(x-a,y-a,z-a); 
  }
  Vec3d operator -() const { 
    return Vec3d(-x,-y,-z); 
  }
  double dot(const Vec3d& b) const {
    return x*b.x+y*b.y+z*b.z;
  }
  static double dot(const Vec3d& a,const Vec3d& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  } 
  Vec3d cross(const Vec3d& b) const {
    return Vec3d(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }
  double magSq() const {
    return x*x+y*y+z*z;
  }
  double mag() const {
    return sqrt(magSq());
  }
  Vec3d mult(double b) const {
    return Vec3d(x*b, y*b, z*b);
  }
  double abs() const {
    return sqrt(magSq());
  }
  double distsq(const Vec3d& b) const {
    double dx = x - b.x, dy = y - b.y, dz = z - b.z; 
    return dx * dx + dy * dy + dz * dz;
  }
  double dist(const Vec3d& b) const {
    return sqrt(distsq(b));
  }
  Vec3d unit() const {
    return mult(1.0/abs());
  }
  static Vec3d unit(double x, double y, double z){
    const double m=1.0/sqrt(x * x + y * y + z * z);
    return Vec3d(m * x, m * y, m * z);
  }
  static Vec3d centroid(const Vec3d vlist[], const int size) {
    double sx = 0, sy = 0, sz = 0;
    for (int i = 1; i < size; ++i) {
      sx += vlist[i].x; sy += vlist[i].y; sz += vlist[i].z;
    }
    const double s = 1.0 / size;
    return Vec3d(s * sx, s * sy, s * sz);
  }
  static Cube boundingCube(const Vec3d vlist[], int const size){ 
    double xmin = vlist[0].x, xmax = vlist[0].x;
    double ymin = vlist[0].y, ymax = vlist[0].y;
    double zmin = vlist[0].z, zmax = vlist[0].z;
    for (int i = 1; i < size; ++i) {
      if (vlist[i].x < xmin)
        xmin = vlist[i].x;
      else if (vlist[i].x > xmax)
        xmax = vlist[i].x;
      if (vlist[i].y < ymin)
        ymin = vlist[i].y;
      else if (vlist[i].y > ymax)
        ymax = vlist[i].y;
      if (vlist[i].z < zmin)
        zmin = vlist[i].z;
      else if (vlist[i].z > zmax)
        zmax = vlist[i].z;
    }
    return Cube(xmin, ymin, zmin, xmax, ymax, zmax);
  }
  double maxDistSq(const Vec3d vlist[], const int size) const {
    double maxDistsq = (*this).distsq(vlist[0]);
    for (int i = 1; i < size; ++i) {
      double dsq = (*this).distsq(vlist[i]);
        if (dsq > maxDistsq)
          maxDistsq = dsq;
    }
    return maxDistsq;
  }
  double maxDist(const Vec3d vlist[], const int size) const {
    return sqrt(maxDistSq(vlist,size));
  }
  static Sphere boundingSphere(const Vec3d vlist[],int size) {
    Vec3d c = centroid(vlist,size);
    return Sphere(c.x,c.y,c.z, c.maxDistSq(vlist,size));
  }
// return the plane for a set of points that minimizes R^2 distances
  static Plane leastSquaresPlane(const Vec3d v[]){
    return Plane(0,0,0,0);
  }
  friend std::ostream& operator <<(std::ostream& s, const Vec3d& v) {
    return s << '(' << v.x << ',' << v.y << ',' << v.z << ')';
  }
};
};
#endif



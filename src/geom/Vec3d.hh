#ifndef VEC3D_HH_
#define VEC3D_HH_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "Sphere.hh"
#include "Cube.hh"
#include "Plane.hh"

namespace geom {

class Vec3d {
public:
  double x,y,z;

  //constructor takes in 3 char*
  Vec3d(char* a, char* b, char* c) {
    x = atof(a);
    y = atof((char*)b);
    z = atof((char*)c);
  }

  //constructor takes in 3 doubles
  Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}

  //addition operator that adds one vector to another
  friend Vec3d operator +(const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x+b.x, a.y+b.y, a.z+b.z);
  }

  //subtraction operator that subtracts one vector from another
  friend Vec3d operator -(const Vec3d& a, const Vec3d& b) {
    return Vec3d(a.x-b.x, a.y-b.y, a.z-b.z);
  }

  //adds a double to the vector
  Vec3d add(double a) const {
    return Vec3d(x+a,y+a,z+a); 
  }

  //operator that switches the direction of the vector
  Vec3d operator -() const { 
      return Vec3d(-x,-y,-z); 
  }

  //subtracts a double from the vector
  Vec3d sub(double a) const {
    return Vec3d(x-a,y-a,z-a); 
  }
  
  //computes the dot product of the vector with another vector
  double dot(const Vec3d& b) const {
    return x * b.x + y*b.y + z*b.z;
  }

  //computes the dot product of any two vectors
  static double dot(const Vec3d& a,const Vec3d& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  } 

  //computes the cross product of the vector with another vector
  Vec3d cross(const Vec3d& b) const {
    return Vec3d(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  }

  //computes the magnitude squared of the vector
  double magSq() const {
    return x*x+y*y+z*z;
  }

  //computes the magnitude of the vector
  double mag() const {
    return sqrt(magSq());
  }

  //multiplies the vector by a double
  Vec3d mult(double b) const {
    return Vec3d(x*b, y*b, z*b);
  }

  //computes the distance squared 
  double distsq(const Vec3d& b) const {
    double dx = x - b.x, dy = y - b.y, dz = z - b.z; 
    return dx * dx + dy * dy + dz * dz;
  }

  //computes the distance 
  double dist(const Vec3d& b) const {
    return sqrt(distsq(b));
  }

  //computes the unit vector
  Vec3d unit() const {
    return mult(1.0/mag());
  }

  //given 3 points, computes the unit vector
  static Vec3d unit(double x, double y, double z){
    const double m=1.0/sqrt(x * x + y * y + z * z);
    return Vec3d(m * x, m * y, m * z);
  }

  //given an array of Vec3d, returns the point at the center
  static Vec3d centroid(const Vec3d vlist[], const int size) {
    double sx = 0, sy = 0, sz = 0;
    for (int i = 1; i < size; ++i) {
      sx += vlist[i].x; sy += vlist[i].y; sz += vlist[i].z;
    }
    const double s = 1.0 / size;
    return Vec3d(s * sx, s * sy, s * sz);
  }

  //return a bounding box for an array of Vec3d
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

  //return the max distance squared between the elements of the Vec3d array
  double maxDistSq(const Vec3d vlist[], const int size) const {
    double maxDistsq = (*this).distsq(vlist[0]);
    for (int i = 1; i < size; ++i) {
      double dsq = (*this).distsq(vlist[i]);
        if (dsq > maxDistsq)
          maxDistsq = dsq;
    }
    return maxDistsq;
  }

  //return the max distance between the elements of the Vec3d array
  double maxDist(const Vec3d vlist[], const int size) const {
    return sqrt(maxDistSq(vlist,size));
  }

  //return the bounding Sphere for an array of Vec3d
  static Sphere boundingSphere(const Vec3d vlist[],int size) {
    Vec3d c = centroid(vlist,size);
    return Sphere(c.x,c.y,c.z, c.maxDistSq(vlist,size));
  }

  // return the plane for a set of points that minimizes R^2 distances
  static Plane leastSquaresPlane(const Vec3d v[], int size){
    return Plane(0,0,0,0);
  }

  friend std::ostream& operator <<(std::ostream& s, const Vec3d& v) {
    return s << '(' << v.x << ',' << v.y << ',' << v.z << ')';
  }
};
};
#endif
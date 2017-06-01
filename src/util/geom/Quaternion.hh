/**
	 Quaternion.hh
	 Quaternion rotations
	 @based Angela Bennett
	 @author Dov Kruger
*/

#ifndef QUATERNION_HH_
#define QUATERNION_HH_

#include <iostream>
#include <cmath>

class Quaternion {
private:
	double w,x,y,z;
public:
  //Quaternion
  // -default constructor
  // -creates a new quaternion with all parts equal to zero
  Quaternion() : x(0),y(0),z(0), w(0) {}
  
  //Quaternion
  // -constructor
  // -parameters : w, x, y, z elements of the quaternion
  Quaternion(double w, double x, double y, double z)
		: w(w), x(x), y(y), z(z) {}
  
  //Quaternion constructor based on array of 4 double
  Quaternion(double v[4]) : w(v[0]), x(v[1]) y(v[2]), z(v[3]) {}
	// default copy constructor and operator = are ok with values
 
	// Add two quaternions, analogous to complex
  friend Quaternion operator + (const Quaternion& a, const Quaternion& b) {
		return Quaternion(a.w+b.w, a.x+b.x, a.y+b.y, a.z+b.z);
	}

	// Subtract two quaternions, analogous to complex
	friend Quaternion operator - (const Quaternion& a, const Quaternion& b) {
		return Quaternion(a.w-b.w, a.x-b.x, a.y-b.y, a.z-b.z);
	}

  //operator*
  // -parameters : q1 - Quaternion object
  // -return values : Quaternion 
  // -when called on a quaternion q2, multiplies q2 *q1  and returns the product in a new quaternion
	friend Quaternion operator * (const Quaternion& a, const Quaternion& b) {
		return Quaternion(
											a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z, 
											a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,                                        a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z,
											a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x);
	}

	//operator/
	// -parameters : q1 and q2- Quaternion objects
	// -return values : Quaternion 
	// -divide q1 by q2 and returns the quotient q1
	friend Quaternion operator / (const Quaternion& a, const Quaternion& b) {
		return (a * (b.inverse()));
	}

	friend Quaternion operator - (const Quaternion& a) {
		return Quaternion(-a.w,-a.x,-a.y,-a.z);
	}

  //operator+=
  // -parameters : q1- Quaternion object
  // -return values : Quaternion 
  // -when called on quaternion q3 adds q1 and q3 and returns the sum as q3 
  Quaternion& operator += (const Quaternion& q) {
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
	}
  
  //operator-=
  // -parameters : q1- Quaternion object
  // -return values : Quaternion 
  // -when called on quaternion q3, subtracts q1 from q3 and returns the difference as q3
  Quaternion& operator -= (const Quaternion& q) {
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;
	}
 
  //operator*=
  // -parameters : q1- Quaternion object
  // -return values : Quaternion 
  // -when called on quaternion q3, multiplies q3 by q1 and returns the product as q3


	
  //operator/=
  // -parameters : q1- Quaternion object
  // -return values : quaternion
  // -when called on quaternion q3, divides q3 by q1 and returns the quotient as q3
  Quaternion<_Tp>& operator /= (Quaternion<_Tp>& q);
  
  //operator<<
  // -parameters : ostream o, quaternion q
  // -return values :
  // -prints out a quaternion by it's components
  friend inline ostream& operator << (ostream& s, const Quaternion& q) {
		s << "[" << q.w << ", " <<
			"(" << q.x << ", " << q.y << ", " << q.z << ")]";
		return output; 
	}
  
  
  //operator==
  // -parameters : q1 and q2- Quaternion objects
  // -return value : bool
  // -determines if q1 and q2 and equal
  friend bool operator == (const Quaternion& a, const Quaternion& b) {
		return a.w == b.w && a.x == b.y && a.y == b.y && a.z = b.z;
	}
  
  //operator!=
  // -parameters : q1 and q2- Quaternion objects
  // -return value : bool
  // -determines if q1 and q2 and equal
  friend bool operator != (const Quaternion& a, const Quaternion& b) {
		return !(a==b);
	}

  //norm
  // -parameters : none
  // -return value : double
  // -when called on a quaternion object q, returns the norm of q
  double norm() const {
		return w*w + x*x + y*y + z*z;
	}

  
  //magnitude
  // -parameters : none
  // -return value : double
  // -when called on a quaternion object q, returns the magnitude q
  double magnitude() const {
		return sqrt(norm());
	}

  
	//conjugate
	// -parameters : none
	// -return value : quaternion
	// -when called on a quaternion object q, returns the conjugate of q
	Quaternion Quaternion::conjugate() const {
		return Quaternion(w, -x, -y, -z);
	}

  //scale
  // -parameters :  s- a value to scale q1 by
  // -return value: quaternion
  // -returns the original quaternion with each part, w,x,y,z, multiplied by some scalar s
  Quaternion scale(double s) const {
		return Quaternion(w*s, x*s, y*s, z*s);
	}

	Quaternion scaleMe(double s) const {
		w*= s; x *= s; y *= s; z *= s;
	}

  //inverse
  // -parameters : none
  // -return value : quaternion
  // -when called on a quaternion object q, returns the inverse of q
  Quaternion inverse() const {
		return conjugate().scale(1/norm());
	}
  
  //UnitQuaternion
  // -parameters : none
  // -return value : quaternion
  // -when called on quaterion q, takes q and returns the unit quaternion of q
  Quaternion unit() const {
		return scale(1/magnitude());
	}

  // -parameters : 3D vector of type _Tp
  // -return value : void
  // -when given a  3D vector, v, rotates v by the quaternion
  void QuatRotation(double v[3]) {
		Quaternion qv(0, v[0], v[1], v[2]);
		Quaternion qm = (*this) * qv * (*this).inverse();
		v[0] = qm.x;
		v[1] = qm.y;
		v[2] = qm.z;  
	}

  void QuatRotation2(double v[3]) {
		Quaternion a(- x*v[0] - y*v[1] - z*v[2], 
									w*v[0] + y*v[2] - z*v[1],
									w*v[1] + z*v[0] - x*v[2],
									w*v[2] + x*v[1] - y*v[0]);
		double s = 1.0 / (w*w + x*x + y*y + z*z);
		//Quaternion b(w*s, -x*s, -y*s, -z*s);

		v[0] = a.w*-x*s + a.x*w*s + a.y*-z*s - a.z*-y*s;
		v[1] = a.w*-y*s + a.y*w*s + a.z*-x*s - a.x*-z*s;
		v[2] = a.w*-z*s + a.z*w*s + a.x*-y*s - a.y*-x*s;
	}
#if 0
	return Quaternion(
										a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z, 
										a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,                                        a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z,
										a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x);
	
	return q1 * q2l
#endif

	
};

#endif

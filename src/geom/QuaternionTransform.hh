#ifndef QUATERNIONTRANSFORM_HH_
#define QUATERNIONTRANSFORM_HH_

class QuaternionTransform {
private:
	double w,x,y,z;  // real and 3 imaginary parts (rotation)
	double tx,ty,tz; // translation part
public:
	QuaternionTransform(double w, double x, double y, double z,
											double tx, double ty, double tz)
		: w(w), x(x), y(y), z(z), tx(tx), ty(ty), tz(tz) {
	}
	void transform(Vec3d& v) {
		double x = v.x, y = v.y, z = v.z;
		v.x = x + tx;
		v.y = y + ty;
		v.z = z + tz;
	}
};

#endif

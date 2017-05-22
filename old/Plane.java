package dovmath;

/**
  Represent a plane in 3d space
  */
public class Plane {
	public double a, b, c, d; // ax+by+cz+d
	//TODO: should we always normalize a,b,c, therefore not needing to divide by magnitude?
	public Plane(double a, double b, double c, double d) {
		this.a = a; this.b = b; this.c = c; this.d = d;
	}
	public Plane(Vec3d p1, Vec3d p2, Vec3d p3) {
		//TODO: define a plane based on three points
	}
	
	//Normalizes Vector by Dividing by Magnitude - Marcin
	public static Vec3d centroid(Vec3d[] points) {
		double sx = 0, sy = 0, sz = 0;
		for (Vec3d p : points) {
			sx += p.x; sy += p.y; sz += p.z;
		}
		double s = 1.0 / points.length;
		return new Vec3d(s*sx, s*sy, s*sz);
	}
	
	//Returns largest variable is - Marcin
	public static double max3(double a, double b, double c) {
		return a > b ? (a > c ? a : c) : (b > c ? b : c);
	}
	
	public static Plane bestFit(Vec3d[] points) {
		final Vec3d s = centroid(points);
		//double sumX = 0, sumY = 0, sumZ = 0;
		double sumXY = 0, sumXZ = 0, sumYZ = 0;
		double sumXX = 0, sumYY = 0, sumZZ = 0;
		for (Vec3d v : points) {
			double dx = v.x - s.x, dy = v.y - s.y, dz = v.z - s.z;
			//sumX += v.x;        sumY += v.y;        sumZ += v.z;
			sumXY += dx * dy; sumXZ += dx * dz; sumYZ += dy * dz;
			sumXX += dx * dx; sumYY += dy * dy; sumZZ += dz * dz;
		}
		double detx = sumYY*sumZZ - sumYZ*sumYZ;
		double dety = sumXX*sumZZ - sumXZ*sumXZ;
		double detz = sumXX*sumYY - sumXY*sumXY;
		double det_max = max3(detx,dety,detz);
		
		if (detx > dety) {
			if (detx > detz) {
				Vec3d v = new Vec3d(1.0, (sumXZ * sumYZ - sumXY * sumZZ) / detx,(sumXY * sumYZ - sumXZ * sumYY) / detx);
			}  
		} 
			else if (det_max == dety) {//What is det_max? 
				double a = (sumYZ*sumXZ - sumXY*sumZZ) / dety;
				double b = (sumXY*sumXZ - sumYZ*sumXX) / dety;
				Vec3d v = new Vec3d(a,1.0,b);
		} 
			else {
				double a = (sumYZ*sumXY - sumXZ*sumYY) / detz;
				double b = (sumXZ*sumXY - sumYZ*sumXX) / detz;
			Vec3d v = new Vec3d(a,b,1.0);
		}
		
		//double det3 = max3(detx,  dety, detz);
		if (detx == det_max){
			double a = 0;
			double b = 0;
			double c = 0;
			double d = 0;
			return new Plane(a,b,c,d);
		}
		return null; //Should be changed to send back proper value
	}
	// return the plane parallel to this one that includes all these points
	public Plane minDist(Vec3d[] vlist) {
		double maxDist = 0;
		for (Vec3d v : vlist) {
			double d = dist(v);
			if (d > maxDist)
				maxDist = d;
		}
		// now add that distance to the current plane
		return new Plane(a, b, c, d); //TODO: change by maxDist, this isn't correct
	}
	
	public String toString() { return a + "x + " + b + "y + " + c + "z + " + d + " = 0"; }
	public final double dist(Vec3d p) {
		return (a * p.x + b * p.y + c * p.z + d) / Math.sqrt(a*a+b*b+c*c);
	}

}

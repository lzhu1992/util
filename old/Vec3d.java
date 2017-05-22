package dovmath; // cute, it works regardless which of us writes it!

import java.util.Scanner;

public class Vec3d {
	public double x,y,z;

	public Vec3d(double x, double y, double z) { this.x = x; this.y = y; this.z = z; }
	public Vec3d(Scanner s) {
		this(s.nextDouble(), s.nextDouble(), s.nextDouble());
	}
	public final String toString() { return x + "," + y + "," + z; }
	public final Vec3d plus(Vec3d b) { return new Vec3d(x+b.x,y+b.y,z+b.z); }
	public final Vec3d minus(Vec3d b) { return new Vec3d(x-b.x,y-b.y,z-b.z); }

	/**

	  if adding to a Vec3d object, this is faster than plus
	 */
	public final Vec3d plusme(Vec3d b) { x += b.x; y += b.y; z += b.z; return this; }

	public final Vec3d subme(Vec3d b) { x -= b.x; y -= b.y; z -= b.z; return this; }
	public final Vec3d multme(double s) { x *= s; y *= s; z *= s; return this; }
	public final Vec3d mult(double s) { return new Vec3d(x*s, y*s, z*s); }
	public final double magsq() { return x*x+y*y+z*z; }
	public final double abs() { return Math.sqrt(magsq()); }
	public final double distsq(Vec3d b) { double dx = x-b.x, dy = y-b.y, dz = z-b.z; return dx*dx+dy*dy+dz*dz; }
	public final double dist(Vec3d b) { return Math.sqrt(distsq(b)); }
	public static double dot(Vec3d a, Vec3d b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	public final double dot(Vec3d b) { return x*b.x+y*b.y+z*b.z; }
	public final Vec3d cross(Vec3d b) {
		return new Vec3d(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	}
	public final Vec3d unit() {
		return multme(1.0 / abs());
	}
	public static Vec3d unit(double x, double y, double z) {
		final double m = 1/Math.sqrt(x*x+y*y+z*z);
		return new Vec3d(m*x,m*y,m*z);
	}
	public static Vec3d centroid(Vec3d[] vlist) {
		double sx = 0, sy = 0, sz = 0;
		for (Vec3d v : vlist) {
			sx += v.x; sy += v.y; sz += v.z;
		}
		final double s = 1.0 / vlist.length;
		return new Vec3d(s*sx,s*sy,s*sz);
	}
	public static Cube boundingCube(Vec3d[] vlist) {
		double xmin = vlist[0].x, xmax = vlist[0].x;
		double ymin = vlist[0].y, ymax = vlist[0].y;
		double zmin = vlist[0].z, zmax = vlist[0].z;
		
		for (int i = 1; i < vlist.length; ++i) {
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
		return new Cube(xmin, ymin, zmin, xmax, ymax, zmax);
	}

	public final double maxDistSq(Vec3d[] vlist) {
		double maxDistsq = this.distsq(vlist[0]);
		for (int i = 1; i < vlist.length; ++i) {
			double dsq = this.distsq(vlist[i]);
			if (dsq > maxDistsq)
				maxDistsq = dsq;
		}
		return maxDistsq;
	}
	public final double maxDist(Vec3d[] vlist) {
		return Math.sqrt(maxDistSq(vlist));
	}
	
	public static Sphere boundingSphere(Vec3d[] vlist) {
		Vec3d c = centroid(vlist);
		return Sphere.rsq(c, c.maxDistSq(vlist));
	}

	// return the plane for a set of points that minimizes R^2 distances
	public static Plane leastSquaresPlane(Vec3d[] v) {
		return new Plane(0,0,0,0);
	}
}

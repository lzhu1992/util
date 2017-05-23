package dovmath;

public class Sphere {
	public double xc,yc,zc, rsq;
	public Vec3d c;

	public Sphere(Vec3d c, double rsq) {
		this.c = c; this.rsq = rsq; //unsure of what's intended here
	}
	public Sphere(double xc, double yc, double zc, double r) {
		this.xc = xc; this.yc = yc; this.zc = zc;
		this.rsq = r*r; //Original : this.rsq -r*r;
	}
	public static Sphere rsq (Vec3d c, double rsq) {//original: public static rsq (Vec3d c, double rsq)
		return new Sphere(c, rsq);
	}
	public String toString() {
		return "Sphere: [" + xc + "," + yc + "," + zc + " r^2=" + rsq + "]";
	}
}
		

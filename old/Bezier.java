package dovmath;

public class Bezier {
	private Vec3d[] p; // control points
	private int used;
	private double[] c; // coefficients

	private void grow() {
		if (used < p.length)
			return;
		Vec3d[] temp = p;
		p = new Vec3d[temp.length * 2];
		System.arraycopy(temp, 0, p, 0, temp.length);
		double[] temp2 = c;
		c = new double[c.length*2];
		System.arraycopy(temp2, 0, c, 0, temp2.length);
	}
	/*
		PCHIP
		dx0 = X1-X0
		dx1 = X2-X1
		X1p = dx1 * dx0.abs() + dx0*dx1.abs()) / (dx1.abs() + dx0.abs());


		x(t) = at^3 + bt^2 + ct + d
		d0 = X0
		b0 = 0
		a + c = X1 - X0
		3a + c = X1p --> 2a + (a+c) = X1p --> 2a = X1p - X1 + X0

		di = Xi
		c = Xip
		ai + bi = X1 - X0 - Xip
		3ai + 2bi = Xi+1p - Xip
		ai + 2(ai+bi) = Xi+1p - Xip
		ai = Xi+1p - Xip - 2(X1 - X0 - Xip) = Xi+1p +Xip - 2(X1-X0)
		bi = X1 - X0 - Xip - (Xi+1p +Xip - 2(X1-X0)) = 3(X1-X0) - Xi+1p


	 */


	private void computeCoefs() {
		//(1–t)^3P0+3(1–t)^2tP1+3(1–t)t^2 P2+ t^3 P3 
		for (int i = 0; i < used; i+=3) {
			computeOneSegment(i);
		}
	}
	private final void computeOneSegment(int i) {
		computeOneVar(4*i, p[i].x, p[i+1].x, p[i+2].x, p[i+3].x);
		computeOneVar(4*i+4, p[i].y, p[i+1].y, p[i+2].y, p[i+3].y);
		computeOneVar(4*i+8, p[i].x, p[i+1].x, p[i+2].x, p[i+3].x);		
	}
	private final void computeOneVar(int i, double p0, double p1, double p2, double p3) {
		//(1-t)(1-t) = 1 - 2t + t^2
		//(1 - 2t + t^2)(1-t) = 1 - 2t + t^2 - t + 2t^2 - t^3 = (1 - 3t + 3t^2 - t^3)P0
		//3(1-t)^2 t = 3t(1-2t+t^2) = (3t - 6t^2 + 3t^3)P1
		//3(1-t)t^2 = (3t^2 - 3t^3)P2
		//t^3 P3
		// t^3(p3-4p2+p1-p0)
		//@t=1 1-3+3-1 = 0p0 + 3-6 + 3 = 0p1 + 3 - 3 = 0p2 + p3 = check!
		//derivative: (-3t^2+6t -3)P0 + (3 - 12t + 9t^2)P1 + (6t - 6t^2)P2 + 3t^2P3

		c[i] = -p0 + 3*(p1+p2);
		c[i+1] = 3*(p0 + p2 -2*p1);
		c[i+2] = 3*(p1-p0);
		c[i+3] = p0;
	}
	
	public Bezier() {
		p = new Vec3d[3];
		used = 0;
		c = new double[12];
		computeCoefs();
	}
	
	public Bezier(Vec3d[] v) {
		p = v.clone();
		used = v.length;
		c = new double[4*v.length];
		computeCoefs();
	}
	public void computePoints(float[] pts, double dt) {
		int j = 0;
		for (int i = 0; i < used; i+= 12) {
			for (double t = 0; t <= 1; t += dt) {
				pts[j++] = (float)(((c[i]*t+c[i+1])*t+c[i+2])*t+c[i+3]);
				pts[j++] = (float)(((c[i+4]*t+c[i+5])*t+c[i+6])*t+c[i+7]);
				pts[j++] = (float)(((c[i+4]*t+c[i+5])*t+c[i+6])*t+c[i+7]);
			}
		}
	}
	public void addPoint(double x, double y, double z) {
		Vec3d v = new Vec3d(x,y,z);
		addPoint(v);
	}
	public void addPoint(Vec3d v) {
		grow();
		p[used] = v;
		computeOneSegment(used++);
	}
}
	

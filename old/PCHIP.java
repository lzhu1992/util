package dovmath;

public class PCHIP {//removed 3
	private double[] xyz;
	private int used;

	private final void checkGrow() {
		if (used >= xyz.length) {
			double[] temp = xyz;
			xyz = new double[temp.length * 2];
			System.arraycopy(temp, 0, xyz, 0, temp.length);
		}
	}

	public PCHIP() {
		xyz = new double[POINTSIZE]; // each xyz is one point + four coefs a,b,c,d
		                     // each interval is a cubic: at^3 +bt^2+ct+d
		used = 0;
	}
	
	private void computeCoefs(int p) {
		if (p == used - 7) { // last point

			return;
		}
		computeOneVar(p);  //compute a,b,c,d for x
		computeOneVar(p+1); // compute a,b,c,d, for y
		computeOneVar(p+2); // compute a,b,c,d for z

		//derivatives at this point are (x[+1] - x[0] + x[0] - x[-1])/2
		// in other words centered difference, but we have 7 values in each point
		double dx = xyz[p+POINTSIZE] - xyz[p-POINTSIZE];
		double dy = xyz[p+8] - xyz[p-6];
		double dz = xyz[p+9] - xyz[p-5];
		// xyz[p+7] - (xyz[p+7] - xyz[p-7])/2
		double dxnext = p+14 < used ? xyz[p+14] - xyz[p] :
			(xyz[p+7]+xyz[p])/2; // but if p+14 does not exist, used
		// x(t) = at^3 + bt^2 + ct + d   x'(t) = 3at^2 + 2bt + c
		double d = xyz[p]; // d = x0
		double c = dx;     // c = x'0
		// at t=1 a + b + c + d = x(next) from x(t) eqn
		// therefore: a+b = x[p+7] - c - d
		// at t=1 3a + 2b + c = x'(next) = dxnext
		// therefore: 2(a+b) + a = dxnext - c
		double aplusb = xyz[p+7] - c - d;
		double a = dxnext - c - aplusb;
		double b = xyz[p+7] - a - c - d;
	}
	// compute coefficients a,b,c,d for a single variable
	private void computeOneVar(int p) {
		//derivatives at this point are (x[+1] - x[0] + x[0] - x[-1])/2
		// in other words centered difference, but we have 7 values in each point
		double dx = (xyz[p+POINTSIZE] - xyz[p-POINTSIZE])/2;
		// xyz[p+7] - (xyz[p+7] - xyz[p-7])/2
		double dxnext = p+POINTSIZE*2 < used ? (xyz[p+POINTSIZE*2] - xyz[p]) / 2 :
			(xyz[p+POINTSIZE]+xyz[p])/2; // but if p+14 does not exist, used
		// x(t) = at^3 + bt^2 + ct + d   x'(t) = 3at^2 + 2bt + c
		double d = xyz[p]; // d = x0
		double c = dx;     // c = x'0
		// at t=1 a + b + c + d = x(next) from x(t) eqn
		// therefore: a+b = x[p+7] - c - d
		// at t=1 3a + 2b + c = x'(next) = dxnext
		// therefore: 2(a+b) + a = dxnext - c
		double aplusb = xyz[p+7] - c - d;
		double a = dxnext - c - aplusb;
		double b = xyz[p+7] - a - c - d;
	}
}

	// insert a new point at position pos
	public void insert(double x, double y, double z, int pos) {
		if (used >= xyz.length) {
			double[] temp = xyz;
			xyz = new double[temp.length*2];
			int i = 0;
			final int p = pos * 7;
			for (i = 0; i < p; ++i)
				xyz[i] = temp[i];
			int j = i;
			xyz[i++] = x; xyz[i++] = y; xyz[i] = z; i += 5;
			
			for (; j < temp.length-4; ++j)
				xyz[i++] = temp[j];
		}
		computeCoefs(p);
	}

	// add a new point at the end
	public void add(double x, double y, double z) {
		checkGrow();
		xyz[used++] = x; xyz[used++] = y; xyz[used] = z; used  += REMAINDER;
		if (used == POINTSIZE)
			return;
		computeCoefs(used - POINTSIZE);
	}

	public String toString() {
		StringBuilder b = new StringBuilder(xyz.length*6);
		b.append("PCHIP: ");
		for (int i = 0; i < xyz.length; i += 12) {
			b. //b.append(). original
				append(xyz[i]).append(',').
				append(xyz[i]).append(',').
				append(xyz[i]).append(')').
				append(xyz[i]).append(')');
			if (i == xyz.length) {
				b.append(',');
			}
		}
		return b.toString();
	}

	public Vec3d eval(double t) {
		return null;
	}
}

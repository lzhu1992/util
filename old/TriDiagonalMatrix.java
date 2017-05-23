package dovmath;

import java.io.*;
import java.util.*;
public class TriDiagonalMatrix {
	private double[] m;
	private int n;
	public TriDiagonalMatrix(int n) {
		this. n = n;
		m = new double[3*n-2];
	}
	public TriDiagonalMatrix(Scanner s) {
		this. n = s.nextInt();
		m = new double[3*n-2];
		for (int i = 0; i < 3*n-2; i++)
			m[i] = s.nextDouble();
	}
	public void set(int i, int j, double v) {
		m[2*i+j] = v;
	}
	public double get(int i, int j) {
		if (Math.abs(i-j) > 1)
			return 0;
		return m[2*i+j];
	}
	public String toString() {
		StringBuilder b = new StringBuilder();
		b.append(m[0]).append('\t').append(m[1]);
		for (int j = 2; j < n; j++)
			b.append(0).append('\t');
		b.append('\n');
		int pos = 2;
		for (int i = 1; i < n-2; i++, pos += 3) {
			for (int j = 0; j < i-1; j++)
				b.append(0).append('\t');
			b.append(m[pos]).append('\t').append(m[pos+1]).append('\t').append(m[pos+2]).append('\t');
			for (int j = i+2; j < n; j++)
				b.append(0).append('\t');
			b.append('\n');
		}
		for (int j = 2; j < n; j++)
			b.append(0).append('\t');
		b.append(m[pos]).append('\t').append(m[pos+1]);
		b.append('\n');
		return b.toString();
	}
	public int getSize() { return n; }
	// solve simultaneous equations
	public void solve(double[] x, double[] B) {
		double s = -m[2]/m[0];
		m[2] = 0;
		m[3] += m[1] * s;
		int pos = 3; // first element is position 0, below it is +2
		for (int i = 0; i < n-2; i++, pos += 3) {
			s = -m[pos+2]/m[pos]; // calculate the ratio needed to zero out element below
			m[pos+2] = 0;
			m[pos+3] += m[pos+1]*s;
		}
		System.out.println(this);

	}
	public void splineSolve(double[] D, double[] X) {
		final int n = X.length;
		double[] m = new double[n]; //TODO: put in a class and retain memory
		double[] Y = new double[n];
		Y[0] = X[1] - X[0];
		for (int i = 1; i < n-1; ++i)
			Y[i] = 3*(X[i+1] - X[i-1]);
		Y[n-1] = X[n-1] - X[n-2];
		double s = -0.5; // first ratio = -1.0/2
		Y[1] += Y[0]*s;
		m[1] = 4 + s; // modify every row after the first from the original 4.0 on main diagonal
		for (int i = 1; i < n-1; i++) {
			s = -1/m[i]; // the factor to wipe out the cell below this one
			m[i+1] = 4 + s;
			Y[i+1] = Y[i+1]+ s*Y[i];
		}
		for (int i = n-1; i > 0; i--) {
			D[i] = Y[i] / m[i];
			Y[i-1] -= D[i];
			System.out.println(m[i] + "\t" + D[i] + "\t" + Y[i]);
		}
		Y[0] = (Y[0] - D[1]) * .5;
		System.out.println(m[0] + "\t" + D[0] + "\t" + Y[0]);		
	}
	public static void main(String[] args) throws IOException {
		Scanner s = new Scanner(new FileReader("src/dovmath/tridiagonalmatrix.dat"));
		TriDiagonalMatrix m = new TriDiagonalMatrix(s);
		System.out.println(m);
		int n = m.getSize();
		double[] x = new double[n];
		double[] B = new double[n];
		m.solve(x, B);
		m.splineSolve(x, B);
	}
}

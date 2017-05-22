package dovmath;
import java.nio.FloatBuffer;

/**
 * Represents a 4x4-Matrix in double precision for computation accuracy
 * @author: Dov Kruger
 * Based on matrix by Heiko Brumme
 */

public class Matrix44 {
	private double a, b, c, d;
	private double e, f, g, h;
	private double i, j, k, l;
	private double m, n, o, p;

	/**
     * Creates a 4x4 identity matrix.
     */
    public Matrix44() {
        setIdentity();
    }

    public Matrix44(
    	double c00, double c01, double c02, double c03,
    	double c10, double c11, double c12, double c13,
    	double c20, double c21, double c22, double c23,
   		double c30, double c31, double c32, double c33) {
    	a = c00;	b = c01;	c = c02;	d = c03;
    	e = c10;	f = c11;	g = c12;	h = c13;
    	i = c20;	j = c21;	k = c22;	l = c23;
    	m = c30;	n = c31;	o = c32;	p = c33;
    }
    /**
     * Sets this matrix to the identity matrix.
     */
    public final void setIdentity() {
        a = 1;	b = 0;	c = 0;	d = 0;
        e = 0;	f = 1;	g = 0;	h = 0;
        i = 0;	j = 0;	k = 1;	l = 0;
        m = 0;	n = 0;	o = 0;	p = 1;
    }

    /**
     * Adds this matrix to another matrix.
     *
     * @param other The other matrix
     *
     * @return Sum of this + other
     */
    public Matrix44 add(Matrix44 r) {
        return new Matrix44(
        	a+r.a, b+r.b, c+r.c, d+r.d,
        	d+r.e, f+r.f, g+r.g, h+r.h,
        	i+r.i, j+r.j, k+r.k, l+r.l,
        	m+r.m, n+r.n, o+r.o, p+r.p
        );
    }

    /**
     * Compute this - other matrix.
     *
     * @param b the other matrix
     *
     * @return this - other
     */
    public Matrix44 sub(Matrix44 r) {
        return new Matrix44(
           	a+r.a, b+r.b, c+r.c, d+r.d,
           	d+r.e, f+r.f, g+r.g, h+r.h,
           	i+r.i, j+r.j, k+r.k, l+r.l,
           	m+r.m, n+r.n, o+r.o, p+r.p
        );
    }

    /**
     * Negates this matrix.
     *
     * @return Negated matrix
     */
    public Matrix44 negate() {
        return new Matrix44(
               	-a, -b, -c, -d,
               	-e, -f, -g, -h,
               	-i, -j, -k, -l,
               	-m, -n, -o, -p
           );
    }

    /**
     * Multiplies this matrix with a scalar.
     *
     * @param scalar The scalar
     *
     * @return Scalar product of this * scalar
     */
    public Matrix44 multiply(double s) {
        return new Matrix44(
               	a*s, b*s, c*s, d*s,
               	e*s, f*s, g*s, h*s,
               	i*s, j*s, k*s, l*s,
               	m*s, n*s, o*s, p*s
           );
    }

    public Vec3d xform(Vec3d v) {
    	return new Vec3d(
    		a*v.x + b*v.y + c*v.z + d,
    		e*v.x + f*v.y + g*v.z + h,
    		i*v.x + j*v.y + k*v.z + l
    	);    			
    }
    public void xform(Vec3d[] vlist) {
    	for (Vec3d v : vlist) {
    		double
    			x = a*v.x + b*v.y + c*v.z + d,
    			y = e*v.x + f*v.y + g*v.z + h,
    			z = i*v.x + j*v.y + k*v.z + k;
    		v.x = x; v.y = y; v.z = z;
    	}
    }

    public void rotateMeY(double ang) {
    	double cosa = Math.cos(ang), sina = Math.sin(ang);
    	/*
    	 *   a b c d		cosa  0    -sin   0
    	 *   e f g h		0     1    0      0
    	 *   i j k l		sina  0    cosa   0
    	 *   m n o p		0     0    0      1
    	 * Multiplied:
    	 *   a*cosa + c*sina	b	-a*sina+c*cosa	d
    	 *   e*cosa + g*sina	f	-e*sina+g*cosa	h
    	 *   i*cosa + k*sina	j	-i*sina+k*cosa	l
    	 *   m*cosa + o*sina	n	-m*sina+o*cosa	p	
    	 */
    	
    	double t;
    	t = a; a = t*cosa + c*sina; c = -t*sina + c*cosa;
    	t = e; e = t*cosa + g*sina; g = -t*sina + g*cosa;
    	t = i; i = t*cosa + k*sina; k = -t*sina + k*cosa;
    	t = m; m = t*cosa + o*sina; o = -t*sina + o*cosa;
    }

    public void rotateMeZ(double ang) {
    	double cosa = Math.cos(ang), sina = Math.sin(ang);
    	/*
    	 *   a b c d		cosa  -sin 0      0
    	 *   e f g h		sina  cosa 0      0
    	 *   i j k l		0     0    1      0
    	 *   m n o p		0     0    0      1
    	 * Multiplied:
    	 *   a*cosa + b*sina	-a*sina+b*cosa	c	d
    	 *   e*cosa + f*sina	-e*sina+f*cosa	g	h
    	 *   i*cosa + j*sina	-i*sina+j*cosa	k	l
    	 *   m*cosa + n*sina	-m*sina+n*cosa	o	p	
    	 */
    	
    	double t;
    	t = a; a = t*cosa + c*sina; c = -t*sina + c*cosa;
    	t = e; e = t*cosa + g*sina; g = -t*sina + g*cosa;
    	t = i; i = t*cosa + k*sina; k = -t*sina + k*cosa;
    	t = m; m = t*cosa + o*sina; o = -t*sina + o*cosa;
    }

    
    /**
     * Multiplies this matrix to another matrix.
     *
     * @param other The other matrix
     *
     * @return Matrix product of this * other
     */
    public Matrix44 multiply(Matrix44 r) {
        return new Matrix44(
        	a*r.a + b*r.e + c*r.i + d*r.m,
        	a*r.b + b*r.f + c*r.j + d*r.n,
        	a*r.c + b*r.g + c*r.k + d*r.o,
        	a*r.d + b*r.h + c*r.l + d*r.p,
 
           	e*r.a + f*r.e + g*r.i + h*r.m,
        	e*r.b + f*r.f + g*r.j + h*r.n,
        	e*r.c + f*r.g + g*r.k + h*r.o,
        	e*r.d + f*r.h + g*r.l + h*r.p,

           	i*r.a + j*r.e + k*r.i + l*r.m,
        	i*r.b + j*r.f + k*r.j + l*r.n,
        	i*r.c + j*r.g + k*r.k + l*r.o,
        	i*r.d + j*r.h + k*r.l + l*r.p,

           	m*r.a + n*r.e + o*r.i + p*r.m,
        	m*r.b + n*r.f + o*r.j + p*r.n,
        	m*r.c + n*r.g + o*r.k + p*r.o,
        	m*r.d + n*r.h + o*r.l + p*r.p
        );
    }

    /**
     * return the transpose of this matrix.
     *
     * @return Transposed matrix
     */
    public Matrix44 transpose() {
        return new Matrix44(
        	a, e, i, m,
        	b, f, j, n,
        	c, g, k, o,
        	d, h, l, p
        );
    }

    /**
     * Stores the matrix in a given Buffer.
     *
     * @param buffer The buffer to store the matrix data
     */
    public void toBuffer(FloatBuffer buffer) {
        buffer.
        	put((float)a).put((float)b).put((float)c).put((float)d).
        	put((float)e).put((float)f).put((float)g).put((float)h).
        	put((float)i).put((float)j).put((float)k).put((float)l).
        	put((float)m).put((float)n).put((float)o).put((float)p).flip();
    }

    public Matrix44 translateMe(double tx, double ty, double tz) {
    	m += tx; n += ty; o += tz;
    	return this;
    }

/*
 * Scale the current matrix by (sx,sy,sz)
 * 
 */
    public Matrix44 scaleMe(double sx, double sy, double sz) {
    	a *= sx; b *= sy; c *= sz;
    	e *= sx; f *= sy; g *= sz;
    	i *= sx; j *= sy; k *= sz;
    	m *= sx; n *= sy; o *= sz;
    	return this;
    }


    /**
     * Creates a translation matrix. Similar to
     * <code>glTranslate(x, y, z)</code>.
     *
     * @param x     x coordinate of translation
     * @param y     y coordinate of translation
     * @param z     z coordinate of translation
     *
     * @return translation matrix
     */
    public static Matrix44 translate(double tx, double ty, double tz) {
        return new Matrix44(
        	1, 0, 0, tx,
        	0, 1, 0, tx,
        	0, 0, 1, tz,
        	0, 0, 0, 1
        );
    }

    /**
     * Creates a rotation matrix. Similar to
     * <code>glRotate(angle, x, y, z)</code>.
     *
     * @param angle Angle of rotation in degrees
     * @param x     x coordinate of the rotation vector
     * @param y     y coordinate of the rotation vector
     * @param z     z coordinate of the rotation vector
     *
     * @return Rotation matrix
     */
    public static Matrix44 rotate(double angle, double x, double y, double z) {
        final double c = Math.cos(Math.toRadians(angle));
        final double s = Math.sin(Math.toRadians(angle));
        //Vec3d vec = Vec3d.unit(x, y, z);

        return new Matrix44(
        	x * x * (1 - c) + c,      x * y * (1 - c) - z * s,   x * z * (1 - c) + y * s,    0,
        	y * x * (1 - c) + z * s,  y * y * (1 - c) + c,       y * z * (1 - c) + x * s,    0,
        	x * z * (1 - c) - y * s,  y * z * (1 - c) - x * s,   z * z * (1 - c) + c,        0,
        	0,                        0,                         0,                          1
        );
    }

    /**
     * Creates a scaling matrix. Similar to <code>glScale(x, y, z)</code>.
     *
     * @param x Scale factor along the x coordinate
     * @param y Scale factor along the y coordinate
     * @param z Scale factor along the z coordinate
     *
     * @return Scaling matrix
     */
    public static Matrix44 scale(double x, double y, double z) {
        return new Matrix44(
        	x, 0, 0, 0,
        	0, y, 0, 0,
        	0, 0, z, 0,
        	0, 0, 0, 1
        );
    }
}

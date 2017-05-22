package dovmath;
import java.nio.FloatBuffer;

/**
 * Represents a 4x4-Matrix in double precision for computation accuracy
 * @author: Dov Kruger
 * Based on matrix by Heiko Brumme
 */

public class Matrix4 {
	private double m00, m01, m02, m03;
	private double m10, m11, m12, m13;
	private double m20, m21, m22, m23;
	private double m30, m31, m32, m33;

	/**
     * Creates a 4x4 identity matrix.
     */
    public Matrix4() {
        setIdentity();
    }

    public Matrix4(
    	double c00, double c01, double c02, double c03,
    	double c10, double c11, double c12, double c13,
    	double c20, double c21, double c22, double c23,
   		double c30, double c31, double c32, double c33) {
    	m00 = c00;	m01 = c01;	m02 = c02;	m03 = c03;
    	m10 = c10;	m11 = c11;	m12 = c12;	m13 = c13;
    	m20 = c20;	m21 = c21;	m22 = c22;	m23 = c23;
    	m30 = c30;	m31 = c31;	m32 = c32;	m33 = c33;
    }
    /**
     * Creates a 4x4 matrix with specified columns.
     */
/*    public Matrix4(Vector4f col1, Vector4f col2, Vector4f col3, Vector4f col4) {
        m00 = col1.x;	     m01 = col2.x;        m02 = col3.x;        m03 = col4.x;
        m10 = col1.y;        m11 = col2.y;        m12 = col3.y;        m13 = col4.y;
        m20 = col1.z;        m21 = col2.z;        m22 = col3.z;        m23 = col4.z;
        m30 = col1.w;        m31 = col2.w;        m32 = col3.w;        m33 = col4.w;
    }
*/
    /**
     * Sets this matrix to the identity matrix.
     */
    public final void setIdentity() {
        m00 = 1;	m01 = 0;	m02 = 0;	m03 = 0;
        m10 = 0;	m11 = 1;	m12 = 0;	m13 = 0;
        m20 = 0;	m21 = 0;	m22 = 1;	m23 = 0;
        m30 = 0;	m31 = 0;	m32 = 0;	m33 = 1;
    }

    /**
     * Adds this matrix to another matrix.
     *
     * @param other The other matrix
     *
     * @return Sum of this + other
     */
    public Matrix4 add(Matrix4 b) {
        return new Matrix4(
        	m00+b.m00, m01+b.m01, m02+b.m02, m03+b.m03,
        	m10+b.m10, m11+b.m11, m12+b.m12, m13+b.m13,
        	m20+b.m20, m21+b.m21, m22+b.m22, m23+b.m23,
        	m30+b.m30, m31+b.m31, m32+b.m32, m33+b.m33
        );
    }

    /**
     * Adds this matrix to another matrix.
     *
     * @param other The other matrix
     *
     * @return Sum of this + other
     */
    public Matrix4 sub(Matrix4 b) {
        return new Matrix4(
        	m00-b.m00, m01-b.m01, m02-b.m02, m03-b.m03,
        	m10-b.m10, m11-b.m11, m12-b.m12, m13-b.m13,
        	m20-b.m20, m21-b.m21, m22-b.m22, m23-b.m23,
        	m30-b.m30, m31-b.m31, m32-b.m32, m33-b.m33
        );
    }

    /**
     * Negates this matrix.
     *
     * @return Negated matrix
     */
    public Matrix4 negate() {
    	return new Matrix4(
    		-m00, -m01, -m02, -m03,
    		-m10, -m11, -m12, -m13,
    		-m20, -m21, -m22, -m23,
    		-m30, -m31, -m32, -m33
    	);
    }

    /**
     * Multiplies this matrix with a scalar.
     *
     * @param scalar The scalar
     *
     * @return Scalar product of this * scalar
     */
    public Matrix4 multiply(double s) {
        return new Matrix4(
        	m00*s, m01*s, m02*s, m03*s,
        	m10*s, m11*s, m12*s, m13*s,
        	m20*s, m21*s, m22*s, m23*s,
        	m30*s, m31*s, m32*s, m33*s
        );
    }

    /**
     * Multiplies this matrix to a vector.
     *
     * @param vector The vector
     *
     * @return Vector product of this * other
     */
    
   /*
    public Vector4f multiply(Vector4f vector) {
        float x = this.m00 * vector.x + this.m01 * vector.y + this.m02 * vector.z + this.m03 * vector.w;
        float y = this.m10 * vector.x + this.m11 * vector.y + this.m12 * vector.z + this.m13 * vector.w;
        float z = this.m20 * vector.x + this.m21 * vector.y + this.m22 * vector.z + this.m23 * vector.w;
        float w = this.m30 * vector.x + this.m31 * vector.y + this.m32 * vector.z + this.m33 * vector.w;
        return new Vector4f(x, y, z, w);
    }
*/
    public Vec3d apply(Vec3d v) {
    	return new Vec3d(
    		m00*v.x + m10*v.y + m20*v.z + m30,
    		m01*v.x + m11*v.y + m21*v.z + m31,
    		m02*v.x + m12*v.y + m22*v.z + m32
    	);    			
    }
    public void apply(Vec3d[] vlist) {
    	for (Vec3d v : vlist) {
    		double
    			x = m00*v.x + m10*v.y + m20*v.z + m30,
    			y = m01*v.x + m11*v.y + m21*v.z + m31,
    			z = m02*v.x + m12*v.y + m22*v.z + m32;
    		v.x = x; v.y = y; v.z = z;
    	}
    }

    
    /**
     * Multiplies this matrix to another matrix.
     *
     * @param other The other matrix
     *
     * @return Matrix product of this * other
     */
    public Matrix4 multiply(Matrix4 b) {
        return new Matrix4(
        	m00 * b.m00 + m01*b.m10 + m02*b.m20 + m03*b.m30,
        	m00 * b.m01 + m01*b.m11 + m02*b.m21 + m03*b.m31,
        	m00 * b.m02 + m01*b.m12 + m02*b.m22 + m03*b.m32,
        	m00 * b.m03 + m01*b.m13 + m02*b.m23 + m03*b.m33,
 
           	m10 * b.m00 + m11*b.m10 + m12*b.m20 + m13*b.m30,
        	m10 * b.m01 + m11*b.m11 + m12*b.m21 + m13*b.m31,
        	m10 * b.m02 + m11*b.m12 + m12*b.m22 + m13*b.m32,
        	m10 * b.m03 + m11*b.m13 + m12*b.m23 + m13*b.m33,

           	m20 * b.m00 + m21*b.m10 + m22*b.m20 + m23*b.m30,
        	m20 * b.m01 + m21*b.m11 + m22*b.m21 + m23*b.m31,
        	m20 * b.m02 + m21*b.m12 + m22*b.m22 + m23*b.m32,
        	m20 * b.m03 + m21*b.m13 + m22*b.m23 + m23*b.m33,

           	m30 * b.m00 + m31*b.m10 + m32*b.m20 + m33*b.m30,
        	m30 * b.m01 + m31*b.m11 + m32*b.m21 + m33*b.m31,
        	m30 * b.m02 + m31*b.m12 + m32*b.m22 + m33*b.m32,
        	m30 * b.m03 + m31*b.m13 + m32*b.m23 + m33*b.m33
        );
    }

    /**
     * return the transpose of this matrix.
     *
     * @return Transposed matrix
     */
    public Matrix4 transpose() {
        return new Matrix4(
        	m00, m10, m20, m30,
        	m01, m11, m21, m31,
        	m02, m12, m22, m32,
        	m03, m13, m23, m33
        );
    }

    /**
     * Stores the matrix in a given Buffer.
     *
     * @param buffer The buffer to store the matrix data
     */
    public void toBuffer(FloatBuffer buffer) {
        buffer.
        	put((float)m00).put((float)m10).put((float)m20).put((float)m30).
        	put((float)m01).put((float)m11).put((float)m21).put((float)m31).
        	put((float)m02).put((float)m12).put((float)m22).put((float)m32).
        	put((float)m03).put((float)m13).put((float)m23).put((float)m33).flip();
    }

    /**
     * Creates a orthographic projection matrix. Similar to
     * <code>glOrtho(left, right, bottom, top, near, far)</code>.
     *
     * @param left   Coordinate for the left vertical clipping pane
     * @param right  Coordinate for the right vertical clipping pane
     * @param bottom Coordinate for the bottom horizontal clipping pane
     * @param top    Coordinate for the bottom horizontal clipping pane
     * @param near   Coordinate for the near depth clipping pane
     * @param far    Coordinate for the far depth clipping pane
     *
     * @return Orthographic matrix
     */
    public static Matrix4 orthographic(
    		double left, double right, double bottom, double top, double near, double far) {
        double tx = -(right + left) / (right - left);
        double ty = -(top + bottom) / (top - bottom);
        double tz = -(far + near) / (far - near);

        Matrix4 ortho = new Matrix4();
        ortho.m00 = 2f / (right - left);
        ortho.m11 = 2f / (top - bottom);
        ortho.m22 = -2f / (far - near);
        ortho.m03 = tx;
        ortho.m13 = ty;
        ortho.m23 = tz;

        return ortho;
    }

    /**
     * Creates a perspective projection matrix. Similar to
     * <code>glFrustum(left, right, bottom, top, near, far)</code>.
     *
     * @param left   Coordinate for the left vertical clipping pane
     * @param right  Coordinate for the right vertical clipping pane
     * @param bottom Coordinate for the bottom horizontal clipping pane
     * @param top    Coordinate for the bottom horizontal clipping pane
     * @param near   Coordinate for the near depth clipping pane, must be
     *               positive
     * @param far    Coordinate for the far depth clipping pane, must be
     *               positive
     *
     * @return Perspective matrix
     */
    public static Matrix4 frustum(
    		double left, double right, double bottom, double top, double near, double far) {
        Matrix4 frustum = new Matrix4();

        double a = (right + left) / (right - left);
        double b = (top + bottom) / (top - bottom);
        double c = -(far + near) / (far - near);
        double d = -(2 * far * near) / (far - near);

        frustum.m00 = (2 * near) / (right - left);
        frustum.m11 = (2 * near) / (top - bottom);
        frustum.m02 = a;
        frustum.m12 = b;
        frustum.m22 = c;
        frustum.m32 = -1;
        frustum.m23 = d;
        frustum.m33 = 0;

        return frustum;
    }

    /**
     * Creates a perspective projection matrix. Similar to
     * <code>gluPerspective(fovy, aspec, zNear, zFar)</code>.
     *
     * @param fovy   Field of view angle in degrees
     * @param aspect The aspect ratio is the ratio of width to height
     * @param near   Distance from the viewer to the near clipping plane, must
     *               be positive
     * @param far    Distance from the viewer to the far clipping plane, must be
     *               positive
     *
     * @return Perspective matrix
     */
    public static Matrix4 perspective(double fovy, double aspect, double near, double far) {
        Matrix4 perspective = new Matrix4();

        double f = (float) (1 / Math.tan(Math.toRadians(fovy) / 2));

        perspective.m00 = f / aspect;
        perspective.m11 = f;
        perspective.m22 = (far + near) / (near - far);
        perspective.m32 = -1;
        perspective.m23 = (2 * far * near) / (near - far);
        perspective.m33 = 0;

        return perspective;
    }

    /**
     * Creates a translation matrix. Similar to
     * <code>glTranslate(x, y, z)</code>.
     *
     * @param x x coordinate of translation vector
     * @param y y coordinate of translation vector
     * @param z z coordinate of translation vector
     *
     * @return Translation matrix
     */
    public static Matrix4 translate(double x, double y, double z) {
    	return new Matrix4(
    		1, 0, 0, 0,
    		0, 1, 0, 0,
    		0, 0, 1, 0,
    		x, y, z, 1
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
    public static Matrix4 rotate(double angle, double x, double y, double z) {
        final double c = Math.cos(Math.toRadians(angle));
        final double s = Math.sin(Math.toRadians(angle));
        Vec3d vec = Vec3d.unit(x, y, z);

        return new Matrix4(
        	x * x * (1 - c) + c,      x * y * (1 - c) - z * s,   x * z * (1 - c) + y * s,    0,
        	y * x * (1 - c) + z * s,  y * y * (1 - c) + c,       y * z * (1 - c) + x * s,    0,
        	x * z * (1 - c) - y * s,  y * z * (1 - c) - x * s,   z * z * (1 - c) + c,        0,
        	0,                        0,                         0,                          0
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
    public static Matrix4 scale(double x, double y, double z) {
        return new Matrix4(
        	x, 0, 0, 0,
        	0, y, 0, 0,
        	0, 0, z, 0,
        	0, 0, 0, 0
        );
    }
}

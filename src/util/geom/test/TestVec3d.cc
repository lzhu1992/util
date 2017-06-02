#include "../Vec3d.hh"
using namespace std;
using namespace geom;
#define print(v) cout << #v << ' ' << v << '\n'

/*
	Test all operations for Vec3d
*/
int main() {
	const Vec3d v0('19', '10', '56');				print(v0);
	const Vec3d v1(1, 2, 3);              	print(v1);
	const Vec3d v2(2.5, 3, 4);          	  print(v2);
	const Vec3d v3 = v1 + v2;         	  	print(v3);
	Vec3d v4 = v1 - v2;             	    	print(v4);
	Vec3d v5 = -v3;               	    	  print(v5);
	Vec3d v6 = v1.cross(v2);   		   	      print(v6);
	Vec3d v7 = v1.mult(3);          	    	print(v7);
	Vec3d v8 = v1.unit();             		  print(v8);
	Vec3d v9 = Vec3d::unit(1,2,3);    	  	print(v9);
	Vec3d v[] = {v0, v1, v2, v3};						
	Vec3d v10 = Vec3d::centroid(v,3);		   	print(v10);
	Vec3d v11 = v1.add(3);									print(v11);
	Vec3d v12 = v1.sub(5);									print(v12);

	double d1 = v3.magSq();           	  	print(d1);
	double d2 = v3.mag();         		      print(d2);
	double d3 = v1.dot(v2);         	    	print(d3);
	double d4 = Vec3d::dot(v1,v2);    		  print(d4);
	double d5 = v1.distsq(v2);        	  	print(d5);
	double d6 = v1.dist(v2);    	  	      print(d6);
	double d7 = v1.maxDistSq(v,3);		      print(d7);
	double d8 = v1.maxDist(v,3);	    	    print(d8);

	Cube c1 = Vec3d::boundingCube(v,4); 		print(c1);
	Sphere s1 = Vec3d::boundingSphere(v,4); print(s1);
	Plane p1 = Vec3d::leastSquaresPlane(v,4); print(p1);



}

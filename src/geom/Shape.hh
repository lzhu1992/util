#ifndef SHAPE_HH_
#define SHAPE_HH_

class Shape {
public:
	virtual double volume() const = 0;
	virtual double surfaceArea() const = 0;
	virtual Cube boundingBox() const = 0;
	virtual Sphere boundingSphere() const = 0;
	virtual Polyhedron approximate() const = 0;
};

#endif


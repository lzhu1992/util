#ifndef POLYHEDRON_HH_
#define POLYHEDRON_HH_

class Polyhedron {
public:
	Polyhedron(Vec3d vertices[], int n) {

	}
	Polyhedron(const vector<Vec3d>& v) {}
	
	void addVertex(const Vec3d v) {
	}
	void addFace(int i, int j, int k) {}

	// return true if this polyhedron completely contains b
	bool contains(const Polyhedron& b) const {
 		return false;
	}

	bool intersects(const Polyhedron& b) const {
 		return false;
	}

	Cube boundingCube() const {
		return ;
	}

	Sphere boundingSphere() const {
	}
	/*
		return a componentList encoding which polyhedrons in the list fit
		and how they must be transformed in order to fit
	*/
	ComponentList knapsack(const vector<Polyhedron> plist);
};

#endif

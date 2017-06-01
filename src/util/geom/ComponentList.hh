#ifndef COMPONENTLIST_HH_
#define COMPONENTLIST_HH_

#include <iostream>

class ComponentList {
private:
	class ComponentPlacement {
		Polyhedron* p; //TODO: Should this be shared_ptr to control memory?
		QuaternionTransform t;
	};
	vector<ComponentPlacement> list;
public:
	ComponentPlacement() {}
	void add(const Polyhedron & p, QuaternionTransform& t) {
		list.push_back(ComponentPlacement(p, t));
	}
};

#endif

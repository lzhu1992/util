#ifndef UNIT_HH_
#define UNIT_HH_

#include <iostream>
#include <string>

class Unit {
private:
	double val;
	Dimension* dim;
public:
	Unit(double val Dimension* d) :	val(val), dim(dim) {}
	friend std::ostream& operator <<(std::ostream& s, const Unit& u) {
		return s << val << ' ' << u.dim->name;
	}

};
#endif


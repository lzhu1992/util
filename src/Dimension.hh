#ifndef DIMENSION_HH_
#define DIMENSION_HH_

#include <iostream>
#include <string>

class Dimension {
private:
	std::string name;
	int length, mass, time;
public:
	Dimension(int len, int mass, int time) :
		length(len), mass(mass), time(time) {}
	friend std::ostream& operator <<(std::ostream& s, const Dimension& d) {
		return s << "Dimension: " << d.name << ' ' << d.length << ',' <<
			d.mass << ',' << d.time;
	}

};
#endif


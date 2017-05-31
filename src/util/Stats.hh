#ifndef STATS_HH_
#define STATS_HH_

#include <iostream>

class Stats {
private:
	double sum, min, max, mean, var;
	void compute() {


	}
public:
	Stats(double x[], int n) {
		compute();
	}
	double getMean() const { return mean; }
	double getVar() const { return var; }
	double getMax() const { return max; }
	double getMin() const { return min; }
	friend ostream& operator <<(ostream& s, const Stats);
};
	
#endif

//TODO: child class NamedStats with name stored? Stats2 with covariance between two variables?

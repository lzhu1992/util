#include "util/Benchmark.hh"

void f() {
	double sum = 0;
	for (int i = 0; i < 100000000; i++)
		sum += i*i;
}


int main() {
	Benchmark a;

	a.start();
	double sum = 0;
	for (int i = 0; i < 100000000; i++)
		sum += i;
	a.stop();
	cout << a << '\n';

	Benchmark::benchmark(f);
}

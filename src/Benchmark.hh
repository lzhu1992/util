#ifndef BENCHMARK_HH_
#define BENCHMARK_HH_

class Benchmark {
private:
public:
	Benchmark();
	// measure how long it takes to execute a function
	void benchmark(void (*Func)() );
	void start();
	void end();
	uint64_t elapsed() const;
};

#endif
